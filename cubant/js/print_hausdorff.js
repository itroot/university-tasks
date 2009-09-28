const delimiter=";";
const tokens=['0', '1', '2'];
const dimension=4;
var table_size=1;
var stats=[];

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

put("dummy");
for (var i=0;i<dimension;++i) {
    put("  ");
}

for (var y=0; y<table_size; ++y) {
    put(delimiter);
    put(numberToCubantString(y)+" ");
}
put("\n");

for (var x=0; x<table_size; ++x) {
    put(numberToCubantString(x));
    for (var y=0; y<table_size; ++y) {
        put(delimiter);
        for (var z=0; z<dimension; ++z) {
            put(" ");
        }
        var cubant_x=createCubant(numberToCubantString(x));
        var cubant_y=createCubant(numberToCubantString(y));
        var hd=hausdorff(cubant_x,cubant_y)
        put(hd);
        stats[hd]++;
    }
    put("\n");
}

log("Stats: ");
for (var i=0;i<=dimension;++i) {
    put(i+": "+stats[i]+" , ");
}