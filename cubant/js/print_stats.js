const delimiter=";";
const tokens=['0', '1', '2'];
const dimension=3;
var table_size=1;
var stats=[];

var dimensions={};

for (var i=0;i<dimension;++i) {
    table_size*=tokens.length;
    stats.push(0);
}
stats.push(0);

log("Table size: "+table_size+"x"+table_size);


function numberToCubantString(num) {
    var n=num;
    var result="";
    for (var i=0;i<dimension;++i) {
        var token_index=num%tokens.length;
        result=token_index+result;
        if ((dimension-1)!==i) result=','+result;
        num/=tokens.length;
        num=Math.floor(num);
    }
    return '/'+result+'/';
}


function cubantSum(s) { 
    var result=0;
    for (var i=0;i<dimension;++i) {
        result+=parseInt(s.substring(2*i+1,2*i+2));
    }
    return result;
}

var order=[];
for (var i=0;i<table_size;++i) {
    order.push(numberToCubantString(i));
}

function cubantDimension(s) {
    var result=0;
    for (var i=0;i<dimension;++i) {
        if ("2"===s.substring(2*i+1,2*i+2)) {
            ++result;
        }
    }
    return result;
}

function cubantsDims(c1,c2) {
    d1=cubantDimension(c1.toString());
    d2=cubantDimension(c2.toString());
    if (d1>d2) return ""+d2+d1; else return ""+d1+d2;
}

order.sort(function(l,r){
    return cubantDimension(l)-cubantDimension(r);
    //cubantSum(l)-cubantSum(r);
});


function numberToCubantUp(num) {
    return order[num];
}


put("dummy");
for (var i=0;i<dimension;++i) {
    put("  ");
}

for (var y=0; y<table_size; ++y) {
    put(delimiter);
    put(numberToCubantUp(y)+" ");
}
put("\n");

for (var x=0; x<table_size; ++x) {
    put(numberToCubantUp(x));
    for (var y=0; y<table_size; ++y) {
        put(delimiter);
        for (var z=0; z<dimension; ++z) {
            //put(" ");
        }
        var cubant_x=createCubant(numberToCubantUp(x));
        var cubant_y=createCubant(numberToCubantUp(y));
        var hd=hausdorff(cubant_x,cubant_y)
        index=cubantsDims(cubant_x, cubant_y);
        if (undefined===dimensions[index]) dimensions[index]={};
        if (undefined===dimensions[index]["sum"]) dimensions[index]["sum"]=0
        if (undefined===dimensions[index]["count"]) dimensions[index]["count"]=0
        //if (undefined===dimensions["sum_"+index]) dimensions["sum_"+index]=0;
        dimensions[index]["sum"]+=hd;
        dimensions[index]["count"]+=1;
        //put(hd);
        stats[hd]++;
    }
    put("\n");
}
log(dimensions.toSource());

for (item in dimensions) {
   put(item+ " : Distance sum: "+dimensions[item]["sum"]+" , count: "+dimensions[item]["count"]+" = "+(dimensions[item]["sum"]/dimensions[item]["count"])+"\n" )
}

/*
log("Stats: ");
for (var i=0;i<=dimension;++i) {
    put(i+": "+stats[i]+" , ");
}
*/
