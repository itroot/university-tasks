(function() {
  System.setPenWidth(1);
  System.setReperSize(3);
  System.setImageSize(900,600);
  System.setCubantStart(400, 580)
  var cubant=createCubant("/1,2,2,1/");
  System.print(cubant.dimension());
  System.drawCubant(cubant);
  System.setPenWidth(5);
  System.setColor(255,255,0);
  System.drawCubantFromString("/2,1,1/");
  var facets=cubantFacet(cubant);
  System.print(facets.toString())
}
)()
