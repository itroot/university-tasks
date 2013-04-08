/* SHELL
 * AUTHOR: Ivan Tosltosheyev, group 216.
 * Автор: Толстошеев Иван, группа 216.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <setjmp.h>

//Отладка
//#define DEBUG
// Максимальная длина командной строки
#define MAX_COMMAND_LENGTH 1024
// Максимальная длина элементарного выражения-"слова".
#define MAX_ATOM 1024
// Приветствие shell
#define INVITE "*>"


jmp_buf jstart;

char buff[MAX_COMMAND_LENGTH]; //Буфер ввода команды
char curlex[MAX_COMMAND_LENGTH+2]; // Текущая лексема.
int curpoint=0; // Сдвиг - текущая позицию в строке.


struct pidbg { // Элемент списка pid-ов фоновых процессов.
  pid_t pid;
  struct pidbg* nextpid;
};

struct pidbg* startbg=0; // Список всех фоновых процессов.

struct cmds { // Структура одной команды
  char** arrargs;// список из имени команды и аргументов
  char *infile; // переназначенный файл стандартного ввода
  char *outfile; // переназначенный файл стандартного вывода
  int appendfile; // флаг, означающий, что вместо > было написано >> .
  int backgrnd; // =1, если команда подлежит выполнению в фоновом режиме
  int and;  // = 1 если разделитель &&
  int or; // =1 если разделитель ||
  struct cmds* subcmd; // команды для запуска в дочернем shell
  struct cmds* pipe; // следующая команда после “|”
  struct cmds* next; // следующая после “;” (или после “&”)
};

struct cmds* startpoint; // Указатель на начало дерева комманд.

void freemem(struct cmds* cmdstruc);


int err(char* str, int iscritical) { // Функция обработки ошибок
  fprintf(stderr,"%s\n",str);
  if (iscritical) {freemem(startpoint);longjmp(jstart,1);}
  return 1; 
}

void addprc(pid_t prcpid) {
  struct pidbg** tmp=&startbg;
  while(*tmp) tmp=&((*tmp)->nextpid);
  *tmp=malloc(sizeof(struct pidbg));
  (*tmp)->pid=prcpid;
  (*tmp)->nextpid=0;
}

void delprc(pid_t prcpid) {
  struct pidbg** tmp=&startbg;
  struct pidbg* todel;
  while(*tmp) {
    if ((*tmp)->pid==prcpid) {
      todel=*tmp;
      *tmp=(*tmp)->nextpid;
      free(todel);
      return;
    }
    tmp=&((*tmp)->nextpid);
  }
  err("Jobcontrol error : not found in list!",1);
}

void printlist() {
  struct pidbg** tmp=&startbg;
  int status;
  while (*tmp) {
    waitpid((*tmp)->pid,&status,WNOHANG);
    if (WIFEXITED(status)) 
    {
      printf("Done: %d\n",(*tmp)->pid);
      delprc((*tmp)->pid);
      continue;
    } else printf("%d\n",(*tmp)->pid);
    tmp=&((*tmp)->nextpid);
  }
}

int check_sys_cmd(char** cmdname) { // Проверка на "системные" команды. 
  if (!cmdname) return 1;
  if (!strcmp(*cmdname,"exit")) exit(0);
  if (!strcmp(*cmdname,"cd")) {if (chdir(cmdname[1])) {return err("cd: arguments are not correct",0);} else return 0;}
  return 1;
}

int read_until(char* str,char* mask) { // Читает до определенных остановочных символов указанных в mask
  int i=0,j;
  int masklen=strlen(mask);
  for(i=0;i<MAX_ATOM;++i){
    if (str[i]==0) return 0; // Если найден конец строки
    for(j=0;j<masklen;++j)
      if (str[i]==mask[j]) return i; // Возвращается сдвиг
  }
  return err("Bad syntax in command.",1); // Если ничего не найдено, то ошибка.
}

int skip_allof(char* str,char* mask) { // Пропускает символы указанные в mask.
  int i=0,j;
  int k;
  int masklen=strlen(mask);
  for(i=0;i<MAX_ATOM;++i){
    k=0;
    if (str[i]==0) return 0; 
    for(j=0;j<masklen;++j)
      if (str[i]==mask[j]) ++k;
    if (k==0) return i;
  }
  return err("Bad syntax in command.",1); // Если ничего не найдено, то ошибка.
}

void getlex() { // Считывает текущую лексему в curlex
  int tmp;

  if ((buff[curpoint]=='&' && buff[curpoint+1]=='&') || 
    (buff[curpoint]=='|' && buff[curpoint+1]=='|')) {
    curlex[0]=buff[curpoint];
    curlex[1]=buff[curpoint+1];
    curlex[2]='\n';
    curlex[3]='\0';
    curpoint+=2;
#ifdef DEBIG
    printf("@#%s#@\n",curlex);
#endif
    return;
    }
  if (buff[curpoint]==';' ||
      buff[curpoint]=='&' ||
      buff[curpoint]=='|' ||
      buff[curpoint]=='(' ||
      buff[curpoint]==')' ||
      buff[curpoint]=='\n') {
    curlex[0]=buff[curpoint];
    curlex[1]='\n';
    curlex[2]='\0';
    if (buff[curpoint]!='\n') ++curpoint;
#ifdef DEBIG
    printf("@#%s#@\n",curlex);
#endif
    return;
  }
  tmp=read_until(buff+curpoint,";&|()\n");
  if (tmp) strncpy(curlex,buff+curpoint,tmp);
  curlex[tmp]='\n';
  curlex[tmp+1]='\0';
  curpoint+=tmp;
#ifdef DEBIG
  printf("@#%s#@\n",curlex);
#endif
}

char** first_arg(int namesize, char* cbeg) { // Создает динамический массив аргументов.
  char** temp=malloc(2*sizeof(char*));// Создаем массив из двух элементов - указателей
  *temp=malloc(sizeof(char)*(namesize+1)); // Первоый из этих элементов укзывает на имя исполняемого файла.
  strncpy(*temp,cbeg,namesize); (*temp)[namesize]='\0'; // Записываем имя исполняемого файла.
  *(temp+1)=NULL; // Массив должен оканчиваться нулем.
  return temp;
}

char** add_arg(char** listarg, int namesize, char* cbeg) { // Добавляет элементы в днамический массив.
  int i=0;
  char** temp=listarg;
  while (*(temp++)) ++i; // Бежим до нуля, в i количество ненулевых указателей.
  temp=realloc(listarg,(i+2)*sizeof(char*)); // Выделяем память под новый элемент массива.
  *(temp+i)=malloc(sizeof(char)*(namesize+1)); // Выделяем память под строчку.
  strncpy(*(temp+i),cbeg,namesize); (*(temp+i))[namesize]='\0'; // Записываем параметр.
  *(temp+i+1)=NULL; // Массив должен оканчиваться нулем.
  return temp;
}

struct cmds* get_command(); // Прототип функции get_command для рекурсии.

struct cmds* get_dummy() { // Возврашает пустой элемент данных
  struct cmds* tmp=malloc(sizeof(struct cmds));
  tmp->arrargs=0;
  tmp->infile=0;
  tmp->outfile=0;
  tmp->appendfile=0;
  tmp->backgrnd=0;
  tmp->and=0;
  tmp->or=0;
  tmp->subcmd=0;
  tmp-> pipe=0;
  tmp->next=0;
  return tmp;
}

struct cmds* get_simple_command() { // Распознает простую команду
  struct cmds* thiscmd = get_dummy();
  int dpoint; // Длина слова.
  int point=0; // Переменая указывающая на конец слова
  char in_or_out; // Принимает значения '<' и '>'. Указывает на вид перенаправления.
  char* command=curlex; // Сформировали комманду.
#ifdef DEBUG
  char** tmpc;
#endif

#ifdef DEBUG
  printf("get_simple_command:#%d >>>%s<<<\n\n",curpoint,curlex);
#endif
  thiscmd->infile=0; thiscmd->outfile=0; thiscmd->appendfile=0; // Первоначальная инциализация флагов и указателей нулями.
  dpoint=skip_allof(command," "); // Пропускаем ведущие пробелы
  point+=dpoint;
  dpoint=read_until(command+point," <>|\n"); // Читаем имя исполняемого файла команды
  if (dpoint==0) {err("Empty command.",1);} // Под вопросом
  thiscmd->arrargs=first_arg(dpoint,command+point); // Добавляем имя командного файла в структуру.
  point+=dpoint;
  while((dpoint=skip_allof(command+point," \n"))) { // Цикл читает аргументы в динамический массив.
    point+=dpoint; // Указатель на начало следующего слова
    if ((command[point]=='<') || (command[point]=='>') || (command[point]=='|')) break; // Аргументы кончились.
    dpoint=read_until(command+point," <>|\n"); // Находим  следующее слово
#ifdef DEBUG
    printf("%d->%d\n",point,dpoint);
#endif 
    thiscmd->arrargs=add_arg(thiscmd->arrargs,dpoint,command+point); // Записываем его в нашу структуру
    point+=dpoint; // Указатель на конец слова
  }
#ifdef DEBUG
  tmpc=thiscmd->arrargs;
  while(*thiscmd->arrargs) printf("@%s@\n",*(thiscmd->arrargs++));//***************************
  thiscmd->arrargs=tmpc;
#endif
  while(command[point]=='>' || command[point]=='<') { // Обрабатываем команды перенаправления.
    in_or_out=command[point]; // Сохраняем вид перенаправления
    ++point; // Сдвигаем указатель
    if (in_or_out=='>' && command[point]=='>') {++point; thiscmd->appendfile=1;} // Если нашли ">>", то appendfile=1
    dpoint=skip_allof(command+point," "); // Пропускаем все возможные пробелы после знаков пернаправления.
    point+=dpoint; // Сдвигаем указатель начала слова.
    dpoint=read_until(command+point," <>|\n"); // Выделяем имя файла.
    if (dpoint==0) err("No argument after '<' or '>' symbols",1); // Если имя пусто - то ошибка.
    if (in_or_out=='>') { // Записываем имя выходного файла в струтуру
      if (thiscmd->outfile) err("Too many output files",1);
      thiscmd->outfile=malloc(sizeof(char)*(dpoint+1));
      strncpy(thiscmd->outfile,command+point,dpoint);
      (thiscmd->outfile)[dpoint]='\0';
    }
    if (in_or_out=='<') { // Записываем имя входного файла в структуру
      if (thiscmd->infile) err("Too many input files",1);
      thiscmd->infile=malloc(sizeof(char)*(dpoint+1));
      strncpy(thiscmd->infile,command+point,dpoint);
      (thiscmd->infile)[dpoint]='\0';
    }
    point+=dpoint;
    dpoint=skip_allof(command+point," "); // Пропускаем все пробелы
    point+=dpoint;
  }
#ifdef DEBUG
  printf("in: @%s@\n",thiscmd->infile);
  printf("out: @%s@\n",thiscmd->outfile);
  printf("outapp: @%d@\n",thiscmd->appendfile);//***********************
#endif
  return thiscmd;
}

struct cmds* get_conveyor() { // Выделяем конвейеры
  struct cmds* thiscmd;
  struct cmds* tmpcmd;

#ifdef DEBUG
  printf("get_conveyor:#%d >>>%s<<<\n\n",curpoint,curlex);
#endif
  thiscmd=get_command();
  thiscmd->pipe=0;
  tmpcmd=thiscmd;
  while (!strcmp(curlex,"|\n")) {
    getlex();
    tmpcmd->pipe=get_command();
    tmpcmd=tmpcmd->pipe;
    tmpcmd->pipe=0;
  }
  return thiscmd;
}

struct cmds* get_list_of_commands() { // Выделяем список команд.
  struct cmds* thiscmd;
  struct cmds* tmpcmd;

#ifdef DEBUG
  printf("get_list_of_commands:#%d >>>%s<<<\n\n",curpoint,curlex);
#endif
  thiscmd=get_conveyor();
  thiscmd->next=0;
  tmpcmd=thiscmd;
  while (!strcmp(curlex,";\n") || !strcmp(curlex,"&\n") || !strcmp(curlex,"&&\n") || !strcmp(curlex,"||\n")) {
    if (!strcmp(curlex,"&\n")) tmpcmd->backgrnd=1; // Флаг исполнения в фоне.
    if (!strcmp(curlex,"&&\n")) tmpcmd->and=1;
    if (!strcmp(curlex,"||\n")) tmpcmd->or=1;
    getlex();
    if (curlex[0]==')' || curlex[0]=='\n') {
#ifdef DEBUG
      printf("**********\n"); // Отладка 
#endif
      return thiscmd;
    }
    tmpcmd->next=get_conveyor();
    tmpcmd=tmpcmd->next;
    tmpcmd->next=0;
  }
  return thiscmd;
}

struct cmds* get_command() { // Выделяем команду
  struct cmds* thiscmd;

#ifdef DEBUG
  printf("get_command:#%d >>>%s<<<\n\n",curpoint,curlex);
#endif
  if (curlex[0]=='(') {
    getlex();
    thiscmd=get_dummy();
    thiscmd->subcmd=get_list_of_commands();
    if (curlex[0]!=')') err("Bracket imbalance.",1);
  } else {thiscmd=get_simple_command();}
  
  getlex();
  return thiscmd;
}

struct cmds* parse() {// Функция преобразования команды во внутреннее представление
  struct cmds* parsecmd;
  parsecmd=get_list_of_commands();
  if (curlex[0]!='\n') err("Bad tail",0);
  return parsecmd;
}

#ifdef DEBUG
int i=0;

void seetree(struct cmds* tmp) {
  int j;
  ++i;
  if (!tmp) {for(j=0;j<i;++j) printf("."); printf("NULL\n"); --i; return;}
  for(j=0;j<i;++j) printf(".");
  if (tmp->arrargs) printf("!%s!\n",*(tmp->arrargs)); else printf("!_!\n");
  if (tmp->next) {for(j=0;j<i;++j) printf(".");printf("NEXT\n");seetree(tmp->next);}
  if (tmp->pipe) {for(j=0;j<i;++j) printf(".");printf("PIPE\n");seetree(tmp->pipe);}
  if (tmp->subcmd) {for(j=0;j<i;++j) printf(".");printf("SCMD\n");seetree(tmp->subcmd);}
  --i;
}

void printstruc(struct cmds* tmp){
 if (tmp->arrargs) printf("%s\n",(tmp->arrargs)[0]);
 // char *infile;
 // char *outfile;
 // int appendfile;
  printf("%d\n",tmp->backgrnd);
  printf("%d\n",tmp->and);
  printf("%d\n",tmp->or);
 // struct cmds* subcmd;
 // struct cmds* pipe;
 // struct cmds* next;
}
#endif

int execute (struct cmds* cmdstruc, int ispipe) { // Выполняет требуемые опреции.
  int status;
  int ppipe[2]; // Связка для PIPE
  int inf,outf; // Файловые дескрипторы для перенапрваления ввода-вывода.
  pid_t curpid;

  if (cmdstruc) {// Если укзатель не пуст.
    if (cmdstruc->arrargs || cmdstruc->subcmd) { // Если есть аргументы у данного узла динамической структуры команд.
      if (cmdstruc->pipe) {
        if(pipe(ppipe)) {fprintf(stderr,"errorpipe\n"); sleep(1);err("pipe",1);} // Если есть конвейер
      }
      if (check_sys_cmd(cmdstruc->arrargs)) {
        if (!(curpid=fork())) { // Исполнение самой команды.
          if (cmdstruc->pipe) { // Выполнение новой команды с конвейером.
            if (cmdstruc->outfile) {
              err("Using '|' and '>' simultaneously. Ignoring '>'.",0);
              free(cmdstruc->outfile);
              cmdstruc->outfile=0; 
            }
            dup2(ppipe[1],1);
            close(ppipe[0]);
            close(ppipe[1]);
          }
          if (ispipe) {
            if (cmdstruc->infile) {
              err("Using '|' and '<' or '<<' simultaneously. Ignoring '<' or '<<'.",0);
              free(cmdstruc->infile);
              cmdstruc->infile=0; 
            }
            dup2(ispipe,0); 
            close(ispipe);
          }
          if (cmdstruc->infile) {  // Ввод с файла.
            if ((inf=open(cmdstruc->infile,O_RDONLY))==-1) {  // Если ошибка открытия на чтение
              free(cmdstruc->infile); 
              cmdstruc->infile=0; 
              err("Error while open file! Using stdin.",0);
            } else { // Если ошибки нет.
              dup2(inf,0);
              close(inf);
            }
          }
          if (cmdstruc->outfile) { // Если есть выходной файл.
            if ((outf=open(cmdstruc->outfile,O_WRONLY|O_CREAT|(cmdstruc->appendfile?O_APPEND:O_TRUNC),0777))==-1) {
              free(cmdstruc->outfile); // Если ошибка открытия на чтение
              cmdstruc->outfile=0; 
              err("Error while open file! Using stdout.",0);
            } else { // Если ошибки нет.
              dup2(outf,1);
              close(outf);
            }
          }
          if (cmdstruc->arrargs) {
            if (execvp(cmdstruc->arrargs[0],cmdstruc->arrargs)) printf("%s - unknown command\n",cmdstruc->arrargs[0]);
          } else if (cmdstruc->subcmd) execute(cmdstruc->subcmd,0);
          exit(0);
        } else if (cmdstruc->backgrnd) addprc(curpid); // Конец fork()
      }
      if (cmdstruc->pipe) {close(ppipe[1]);execute(cmdstruc->pipe,ppipe[0]);close(ppipe[0]);}
      if (!cmdstruc->backgrnd) waitpid(curpid,&status,0);
      while(cmdstruc->next) {
#ifdef DEBUG
        printstruc(cmdstruc);
#endif
        if (cmdstruc->and && !cmdstruc->backgrnd) {
          if (WIFEXITED(status)) {
            if (!WEXITSTATUS(status)) {cmdstruc->and=0;continue;} else {
            cmdstruc=cmdstruc->next;
            continue;
            }
          }
        } else
          if (cmdstruc->or && !cmdstruc->backgrnd) {
            if (WIFEXITED(status)) {
              if (WEXITSTATUS(status)) {cmdstruc->or=0;continue;} else {
              cmdstruc=cmdstruc->next;
              continue;
              }
            }
          } else {
            execute(cmdstruc->next,0);
            break;
          }
      }
    }
  } else err("NULL pointer to the execute position",1); // Ошибка если указатель cmdstruc равен NULL.
  return 0;
}

void freemem(struct cmds* cmdstruc) { // Рекурсивная функций освобождения памяти.
  char** tmp;

  if (cmdstruc) {
#ifdef DEBUG
    printf("freemem\n");
#endif
    free(cmdstruc->infile);
    free(cmdstruc->outfile);
    tmp=cmdstruc->arrargs;
    if (tmp) while (*tmp) {
#ifdef DEBUG
      printf("%s\n",*tmp);
#endif
      free(*(tmp++));}
    free(cmdstruc->arrargs);
    freemem(cmdstruc->next);
    freemem(cmdstruc->pipe);
    freemem(cmdstruc->subcmd);
    free(cmdstruc);
  }
}

int main(int argc, char *argv[]) {
  FILE* cmdf=stdin;
  int showinfo=1;

  if (argc==2) {
    if (!(cmdf=fopen(argv[1],"r"))) { 
      err("Can't open input file; using stdin.",0);
      cmdf=stdin;
    } else showinfo=0;
  }
  while (1) {
    do { // Считываем и преобразовываем строку.
      setjmp(jstart);
      signal(SIGINT,SIG_IGN);
      curpoint=0;
      curlex[0]=0;
      if (showinfo) {
        printlist();
        printf("%s",INVITE);
      }
      if(!fgets(buff,MAX_COMMAND_LENGTH,cmdf)) exit(0);
      buff[MAX_COMMAND_LENGTH]='\n';
      buff[MAX_COMMAND_LENGTH]='\0';
      getlex();
    } while(!(startpoint=parse()) && err("Parsing failed.",0)); // Пока не прочитаем без ошибок.
#ifdef DEBUG
    seetree(startpoint);
#endif
    execute(startpoint,0);
    freemem(startpoint);
  }
}
