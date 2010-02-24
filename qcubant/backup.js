(function() {
  System.setPenWidth(1);
  System.setReperSize(5);
  System.setImageSize(900,800);
  System.setCubantStart(400, 580)

  System.setReper2DVector(0,-100,-50);
  System.setReper2DVector(1,-40,-50);
  System.setReper2DVector(2,0,-50);
  System.setReper2DVector(3,40,-50);
  System.setReper2DVector(4,100,-50);

  var cubant=createCubant("/2,2,2,2,2/");
  System.print(cubant.dimension());
  System.drawCubant(cubant);
  System.setPenWidth(5);
  System.setColor(255,255,0);
  System.drawCubantFromString("/2,1,1/");
  var facets=cubantFacet(cubant);
  System.print(facets.toString())
}
)()
