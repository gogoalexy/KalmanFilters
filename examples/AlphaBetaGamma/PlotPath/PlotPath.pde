import processing.serial.*;
import grafica.*;

Serial serial;
public GPlot plot;
GPointsArray raw, alpha, alpha_beta, alpha_beta_gamma;
int time = 0;

void setup()
{
    size(1024, 768);
    background(0);
    serial = new Serial(this, Serial.list()[0], 9600);
    raw = new GPointsArray();
    alpha = new GPointsArray();
    alpha_beta = new GPointsArray();
    alpha_beta_gamma = new GPointsArray();

    plot = new GPlot(this);
    plot.setPos(60, 60);
    plot.setDim(800, 600);
    plot.getTitle().setText("Alpha-Beta Filters");
    plot.getXAxis().getAxisLabel().setText("Time");
    plot.getYAxis().getAxisLabel().setText("State");
    plot.setPoints(raw);
    plot.setLineColor(color(50, 50, 50, 200));
    plot.addLayer("Alpha", alpha);
    plot.getLayer("Alpha").setLineColor(color(255, 0, 0, 200));
    plot.addLayer("AlphaBeta", alpha_beta);
    plot.getLayer("AlphaBeta").setLineColor(color(0, 255, 0, 200));
    plot.addLayer("AlphaBetaGamma", alpha_beta_gamma);
    plot.getLayer("AlphaBetaGamma").setLineColor(color(0, 0, 255, 200));
}

void draw()
{
    float[] values;
    while( serial.available() > 0) 
    {
        String packet = serial.readStringUntil('\n');
        if(packet != null)
        {
            values = float(split(packet, ','));
            if(values.length == 4)
            {
                raw.add(time, values[0]);
                alpha.add(time, values[1]);
                alpha_beta.add(time, values[2]);
                alpha_beta_gamma.add(time, values[3]);
            }
        }
        else
            continue;
            
      time++;

      plot.beginDraw();
      plot.drawBackground();
      plot.drawBox();
      plot.drawXAxis();
      plot.drawYAxis();
      plot.setPoints(raw);
      plot.setPoints(alpha, "Alpha");
      plot.setPoints(alpha_beta, "AlphaBeta");
      plot.setPoints(alpha_beta_gamma, "AlphaBetaGamma");
      plot.drawLegend(new String[] {"Raw", "alpha", "alpha_beta", "alpha_beta_gamma"}, new float[] {0.1, 0.2, 0.3, 0.45}, new float[] {0.93, 0.93, 0.93, 0.93});
      plot.drawTitle();
      plot.drawLines();
      plot.endDraw();
    }
}
