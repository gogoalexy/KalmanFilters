import processing.serial.*;

// mean = 0
// std = 3
// max = 9 

Serial serial;
Bar[] bars;

class Bar {
    int h, x;
    color c = color(250, 250, 10);
    Bar(int position)
    {
        h = 0;
        x = position*width/21;
        text(str(position-10), x+15, height-10);
    }
    void plot()
    {
        h++;
        fill(c);
        rect(x, height-20, width/21, -h);
    }
}

void setup()
{
    size(630, 400);
    background(0);
    textAlign(CENTER, CENTER);
    serial = new Serial(this, Serial.list()[0], 9600);
    bars = new Bar[21];
    for (int i=0; i<bars.length; i++)
        bars[i] = new Bar(i);
}

void draw()
{
    int region;
    while ( serial.available() > 0) 
    {
        String value = serial.readStringUntil('\n');
        if (value != null)
            region = round(float(value));
        else
            continue;
        
        if(region > 10 || region < -10)
            continue;
        else
            bars[region+10].plot();
            
    }
}
