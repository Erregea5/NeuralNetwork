package visual;

import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.io.File;

public class graphing {
    
    final int xOrigin=300;
    final int yOrigin=500;
    final int xEnd=1000;
    final int yEnd=100;
    int dx;
    int dy;
    final int radius=5;
    ArrayList<Float> vals;
    
    public void setDeltas(){
        dx=(xEnd-xOrigin)/vals.size();
        float max=0,
        min=9999f;
        for(int i=0;i<vals.size();i++){
            float temp=vals.get(i);
            if(max<=temp)
                max=temp;
            if(min>=temp)
                min=temp;
        }
        int adjust=(int)Math.log10(min)-1;
        if(adjust<0 && ((int)Math.log10(max)-adjust)<(int)Math.log10(yOrigin-yEnd)){
            for(int i=0;i<vals.size();i++)
                vals.set(i,vals.get(i)*(float)Math.pow(10, -adjust));
            max*=(float)Math.pow(10, -adjust);
        }
        dy=(yOrigin-yEnd)/(int)max;
        System.out.println(max);
    }
    
    public void scanFile() {
        vals=new ArrayList<>();
        try {
            String in="visual\\history.txt";
            Scanner scan = new Scanner(new File(in));
            /*
            float a=-1.0f; 
            double b=2*Math.PI;
            float delta=.7f;
            in="";
            for(float i=a;i<=b;i+=delta)
                in+=50*Math.sin(i)+" ";//function
            scan=new Scanner(in);
            */
            while (scan.hasNextFloat()) {
                vals.add(scan.nextFloat());
            }
            scan.close();
        }
        catch(Exception e){
            System.err.println(e);
        }
    }
    
    public void createGui(){
        JFrame jf = new JFrame("Loss over time");
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setSize(500,500);
        jf.setLocation(500, 200);
        jf.setVisible(true);
        Container c=jf.getContentPane();
        Panel jp = new Panel(this);
        c.add(jp);
    }
    
    public static void main(String[] args) {
        graphing gr=new graphing();
        gr.scanFile();
        gr.setDeltas();
        gr.createGui();
    }

    class Panel extends JPanel {
        graphing gr;
        Panel(graphing gr) {
            this.gr=gr;
        }

        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawLine(gr.xOrigin, gr.yOrigin, gr.xEnd, gr.yOrigin);
            g.drawLine(gr.xOrigin, gr.yOrigin, gr.xOrigin, gr.yEnd);
            int prevX=gr.xOrigin,prevY=gr.yOrigin;
            for(int i=0;i<vals.size();i++){
                int curX=gr.xOrigin+i*gr.dx;
                int curY=gr.yOrigin-(gr.vals.get(i).intValue())*gr.dy;
                //g.fillOval(curX, curY, radius, radius);
                g.drawLine(curX, curY,prevX,prevY);
                prevX=curX;
                prevY=curY;
                g.drawLine(curX, gr.yOrigin-gr.radius, curX, gr.yOrigin+gr.radius);
                g.drawLine(gr.xOrigin-gr.radius, curY, gr.xOrigin+gr.radius, curY);
            }
        }
    }
}
