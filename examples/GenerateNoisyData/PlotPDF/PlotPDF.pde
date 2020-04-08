import processing.serial.*;
import grafica.*;

int SHIFT = 10;
int CATAGORIES = 21;
// mean = 0
// std = 3
// max = 9 

Serial serial;
int[] gaussianStack;
int[] uniformStack;
float gaussianCounter;
float uniformCounter;
public GPlot gaussianPDF;
public GPlot uniformPDF;

void setup()
{
    size(1024, 768);
    background(0);
    serial = new Serial(this, Serial.list()[0], 9600);

    gaussianCounter = 0.5;
    gaussianStack = new int[CATAGORIES];
    gaussianPDF = new GPlot(this);
    gaussianPDF.setPos(30, 180);
    gaussianPDF.setDim(360, 360);
    gaussianPDF.setYLim(-0.01, 1.0/CATAGORIES + 0.2);
    gaussianPDF.getTitle().setText("Gaussian distribution (" + str(gaussianCounter) + " points)");
    gaussianPDF.getYAxis().getAxisLabel().setText("Relative probability");
    gaussianPDF.startHistograms(GPlot.VERTICAL);
    gaussianPDF.getHistogram().setDrawLabels(true);
    gaussianPDF.getHistogram().setBgColors(new color[] {
    color(0, 0, 255, 50)} );
  
    uniformCounter = 0.5;
    uniformStack = new int[CATAGORIES];
    uniformPDF = new GPlot(this);
    uniformPDF.setPos(530, 180);
    uniformPDF.setDim(360, 360);
    uniformPDF.setYLim(-0.01, 1.0/CATAGORIES + 0.1);
    uniformPDF.getTitle().setText("Uniform distribution (" + str(uniformCounter) + " points)");
    uniformPDF.getXAxis().getAxisLabel().setText("x variable");
    uniformPDF.getYAxis().getAxisLabel().setText("Relative probability");
    uniformPDF.startHistograms(GPlot.VERTICAL);
    uniformPDF.getHistogram().setDrawLabels(true);

}

void draw()
{
    float[] points;
    int gaussianIndex = -1, uniformIndex = -1;
    while( serial.available() > 0) 
    {
        String packet = serial.readStringUntil('\n');
        if(packet != null)
        {
            points = float(split(packet, ','));
            if(points.length == 2)
            {
                gaussianIndex = round(points[0]) + SHIFT;
                uniformIndex = round(points[1]) + SHIFT;
            }
        }
        else
            continue;
        
        GPointsArray gaussianPoints = new GPointsArray(CATAGORIES);
        if(gaussianIndex >=0 && gaussianIndex < gaussianStack.length)
        {
            gaussianStack[gaussianIndex]++;
            gaussianCounter++;
        }
        for(int i = 0; i < gaussianStack.length; i++)
            gaussianPoints.add(i + 0.5 - gaussianStack.length/2.0, gaussianStack[i]/gaussianCounter, str(i - SHIFT));

        gaussianPDF.setPoints(gaussianPoints);
        gaussianPDF.getTitle().setText("Gaussian distribution (" + str(int(gaussianCounter)) + " points)");

        gaussianPDF.beginDraw();
        gaussianPDF.drawBackground();
        gaussianPDF.drawBox();
        gaussianPDF.drawYAxis();
        gaussianPDF.drawTitle();
        gaussianPDF.drawHistograms();
        gaussianPDF.endDraw();
            

        GPointsArray uniformPoints = new GPointsArray(CATAGORIES);
        if(uniformIndex >=0 && uniformIndex < uniformStack.length)
        {
            uniformStack[uniformIndex]++;
            uniformCounter++;
        }
        for(int i = 0; i < uniformStack.length; i++)
            uniformPoints.add(i + 0.5 - uniformStack.length/2.0, uniformStack[i]/uniformCounter, str(i - SHIFT));

        uniformPDF.setPoints(uniformPoints);
        uniformPDF.getTitle().setText("Uniform distribution (" + str(int(uniformCounter)) + " points)");

        uniformPDF.beginDraw();
        uniformPDF.drawBackground();
        uniformPDF.drawBox();
        uniformPDF.drawYAxis();
        uniformPDF.drawTitle();
        uniformPDF.drawHistograms();
        uniformPDF.endDraw();
    }
}
