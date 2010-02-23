(function() {
System.setReperSize(3);
var cubant=createCubant("/1,1,2/");
System.print(cubant.dimension());
System.drawCubantFromString(cubant);
System.setPenWidth(5);
System.drawCubantFromString("/2,1,1/");
}
)()