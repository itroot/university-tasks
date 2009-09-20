#include <string>
#include <iostream>
#include <stdexcept>

#include <fstream>
#include <sstream>

#include <jsapi.h>

#include <cubant/Cubant.hpp>

namespace {
void
errorReporterCallback(JSContext* /*context*/,
                      const char* message,
                      JSErrorReport* report) {
  std::cout << "js:: "
        << (NULL==report->filename?"local":report->filename)
        << ":" << report->lineno << " - " << message 
        << " (what:" << report->errorNumber << ")" << std::cout;
}

}

namespace {
    std::string usage="Usage:\n"
    "cbshell [name of file]\n";
    const uint32 maxbytes=0x1000000;
    const size_t stackchunksize=0x1000;
    JSClass global_class = {
    "global",
    JSCLASS_HAS_PRIVATE,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
    };

    std::string readFile(const std::string& name) {
        using namespace std;
        ifstream in(name.c_str());
        if (!in.good()) {
            throw std::runtime_error("Can't open specified file");
        }
        stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }
}


/**
 * Functions for cubant
 */


namespace {
    JSBool toString(JSContext*, JSObject*, uintN, jsval*, jsval*);

    static JSFunctionSpec cubant_functions[] = {
        {"toString", toString, 0, 0, 0},
        {0,0,0,0,0}
    };
    JSBool toString(JSContext* context, JSObject* object,
                    uintN, jsval* argv, jsval* rval) {
        using namespace CubantCore;
        cubant_t* cubant=static_cast<cubant_t*>(JS_GetPrivate(context, object));
        std::string str=cubant->toString();
        *rval=STRING_TO_JSVAL(JS_NewStringCopyZ(context, str.c_str()));
        return JS_TRUE;
    }

}


/**
 * Global functions
 */
namespace {
    JSBool log(JSContext*, JSObject*, uintN, jsval*, jsval*);
    JSBool put(JSContext*, JSObject*, uintN, jsval*, jsval*);
    JSBool createCubant(JSContext*, JSObject*, uintN, jsval*, jsval*);
    JSBool hausdorff(JSContext*, JSObject*, uintN, jsval*, jsval*);

    static JSFunctionSpec global_functions[] = {
        {"log", log, 1, 0, 0},
        {"put", put, 1, 0, 0},
        {"createCubant", createCubant, 1, 0, 0},
        {"hausdorff", hausdorff, 2, 0, 0},
        {0,0,0,0,0}
    };

    JSBool log(JSContext* context, JSObject*, uintN, jsval* argv, jsval* rval) {
        char* message=JS_GetStringBytes(JS_ValueToString(context, argv[0]));
        std::cerr << "js log: "<< message << std::endl;
        *rval=JSVAL_VOID;
        return JS_TRUE;
    }

    JSBool put(JSContext* context, JSObject*, uintN, jsval* argv, jsval* rval) {
        char* message=JS_GetStringBytes(JS_ValueToString(context, argv[0]));
        std::cout << message;
        *rval=JSVAL_VOID;
        return JS_TRUE;
    }

    JSBool createCubant(JSContext* context, JSObject*,
                        uintN, jsval* argv, jsval* rval) {
        using namespace CubantCore;
        JSObject* result=JS_NewObject(context, &global_class, NULL, NULL);
        *rval=OBJECT_TO_JSVAL(result);
        std::string str=JS_GetStringBytes(JS_ValueToString(context, argv[0]));
        cubant_t* cubant=NULL;
        try {
            // LEAK FIXME
            cubant=new cubant_t(str);
        } catch (std::exception& e) {
            JS_ReportError(context, "Can't create cubant.");
            return JS_FALSE;
        }
        JS_SetPrivate(context, result, cubant);
        if (!JS_DefineFunctions(context, result, cubant_functions)) {
            JS_ReportError(context, "Can't define cubant functions.");
            return JS_FALSE;
        }
        return JS_TRUE;
    }

    JSBool hausdorff(JSContext* context, JSObject*, uintN, jsval* argv, jsval* rval) {
        using namespace CubantCore;
        cubant_t* cubant0=static_cast<cubant_t*>
            (JS_GetPrivate(context, JSVAL_TO_OBJECT(argv[0])));
        cubant_t* cubant1=static_cast<cubant_t*>
            (JS_GetPrivate(context, JSVAL_TO_OBJECT(argv[1])));
        // FIXME HAUSDORFF
        unsigned int result=cubant_t::hausdorf(*cubant0, *cubant1);
        *rval=INT_TO_JSVAL(result);
        return JS_TRUE;
    }
}



/**
 * This code is quite unclean, while it do not frees resourses.
 * But, who cares, when you must just do one pass ;-)
 */

int
main(int argc, char* argv[]) {
    if (2!=argc) {
        std::cout << usage;
    }

    JSRuntime* runtime=JS_NewRuntime(maxbytes);
    if (NULL==runtime) {
        throw std::runtime_error("Can't create JS runtime");
    }

    JSContext* context=JS_NewContext(runtime, stackchunksize);
    if (NULL==context) {
        throw std::runtime_error("Can't create JS context");
    }
    JS_SetErrorReporter(context, errorReporterCallback);

    JSObject* global = JS_NewObject(context, &global_class, NULL, NULL);
    if (NULL==global) {
        throw std::runtime_error("Can't create global object for JS");
    }

    if (!JS_InitStandardClasses(context, global)) {
       throw std::runtime_error("Can't init standart classes");
    }

    if (!JS_DefineFunctions(context, global, global_functions)) {
        throw std::runtime_error("Can't init global functions");
    }

    std::string script=readFile(argv[1]);
    std::cout << "READ SCRIPT: \n===========\n" << script << "\n===========\n";
    std::cout << "EXECUTING..." << std::endl;

    jsval rval;
    JSBool result=
         JS_EvaluateScript(context,
                           global,
                           script.c_str(),
                           script.length(),
                           argv[1],
                           0,
                           &rval);
    if (JS_FALSE==result) {
        throw std::runtime_error("Can't execute script");
    }
    JSString* str=JS_ValueToString(context, rval);
    if (NULL==str) {
        std::cout << "RETURN: Can't convert to string.\n";
    } else {
        std::cout << "RETURN: " << JS_GetStringBytes(str) << "\n";
    }
}
