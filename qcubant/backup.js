(function() {
  System.setPenWidth(1);
  System.setReperSize(9);
  System.setImageSize(900,800);
  System.setCubantStart(400, 580);
  //System.setReper2DVector(0,200,-70);
  System.setColor(150,150,150);

var a1=[
"/2,2,2,0,0,0,0,0,0/",
"/2,2,1,0,0,0,0,0,2/",
"/2,1,1,0,0,0,0,2,2/",
"/1,1,1,0,0,0,2,2,2/",
"/1,1,1,0,0,2,2,2,1/",
"/1,1,1,0,2,2,2,1,1/",
"/1,1,1,2,2,2,1,1,1/",
];

var a2=[
"/0,0,0,2,2,2,0,0,0/",
"/0,0,2,2,2,1,0,0,0/",
"/0,2,2,2,1,1,0,0,0/",
"/2,2,2,1,1,1,0,0,0/",
"/2,2,1,1,1,1,0,0,2/",
"/2,1,1,1,1,1,0,2,2/",
"/1,1,1,1,1,1,2,2,2/"
];

var a3=[

"/0,0,0,0,0,0,2,2,2/",
"/0,0,0,0,0,2,2,2,1/",
"/0,0,0,0,2,2,2,1,1/",
"/0,0,0,2,2,2,1,1,1/",
"/0,0,2,2,2,1,1,1,1/",
"/0,2,2,2,1,1,1,1,1/",
"/2,2,2,1,1,1,1,1,1/"
]
  var whole=createCubant("/2,2,2,2,2,2,2,2,2/");
  System.setPenWidth(1);
  System.drawCubant(whole);
  System.setColor(0,0,0);
  System.setColor(255,0,0);
  System.setPenWidth(2);
  for (e in a1) {
    System.drawCubantFromString(a1[e]);
  }

  System.setColor(0,255,0);
  for (e in a2) {
    System.drawCubantFromString(a2[e]);
  }
  System.setColor(0,0,255);
  for (e in a3) {
    System.drawCubantFromString(a3[e]);
  }
}
)()
