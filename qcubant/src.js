function setReper() {
    const num=4;
    const width=30;
    const height=60;
    System.setReperSize(num);
    for (var i=0; i<num; ++i) {
        var x=Math.floor(width*(i-Math.floor(num/2))+((num%2)?0:width/2));
        var y=-height/((Math.abs((num)/2.0-i-0.5)+1));
        //if (i<4) {
        //    x=-x;
        //    y=-y;
        //}
        System.setReper2DVector(i, x, y);
        System.print(i+": "+x+" => "+y);
    }
}

function drawReper() {
    System.setColor(255,150,150);
    System.drawReper();
}

(function() {
  System.setPenWidth(2);
  System.setImageSize(900,800);
  System.setCubantStart(400, 580);
  setReper();
  drawReper();
  System.drawCubant(createCubant("/2,2,2,2/"));
}
)()
