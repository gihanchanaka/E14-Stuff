import oracle.jrockit.jfr.JFR;

import javax.swing.*;
import java.awt.*;

public class ScorePanel {
    static JFrame scoreFrame=new JFrame("Score board");;
    static JPanel scorePanel;
    static String temp;
    static GridBagConstraints gbc=new GridBagConstraints();
    public static void buildGUI(){
        gbc.fill = GridBagConstraints.BOTH;
        scorePanel=new JPanel(new GridBagLayout());
        scorePanel.setPreferredSize(new Dimension(1500,700));

        scorePanel.setBackground(Color.BLACK);
        scorePanel.setOpaque(true);
/////
        JPanel jp_score_wickets=new JPanel(new GridBagLayout());
        JLabel jl_score_wickets=new JLabel("SCORE - WICKETS");
        jl_score_wickets.setBackground(Color.WHITE);
        jl_score_wickets.setBackground(Color.BLACK);
        jl_score_wickets.setOpaque(false);
        jl_score_wickets.setFont(new Font("Serif",Font.BOLD,30));
        jl_score_wickets.setSize(1500,100);

        temp=Driver.score+"-"+Driver.wickets;
        while(temp.length()<5)temp=" "+temp;
        JLabel score_wickets=new JLabel(temp);
        score_wickets.setFont(new Font("Serif",Font.BOLD,400));
        score_wickets.setSize(1500,200);
        score_wickets.setForeground(Color.WHITE);
        score_wickets.setBackground(Color.BLACK);
        score_wickets.setOpaque(true);

        gbc.gridx=0;
        gbc.gridy=0;
        jp_score_wickets.add(jl_score_wickets,gbc);
        gbc.gridy=1;
        jp_score_wickets.add(score_wickets,gbc);
////

/////
        JPanel jp_balls=new JPanel(new GridBagLayout());

        JLabel jl_balls=new JLabel("OVERS");
        jl_balls.setBackground(Color.WHITE);
        jl_balls.setBackground(Color.BLACK);
        jl_balls.setOpaque(false);
        jl_balls.setFont(new Font("Serif",Font.BOLD,30));
        jl_balls.setSize(1500,100);

        temp=(Driver.totalBalls/6)+"."+(Driver.totalBalls%6);
        while(temp.length()<5)temp=" "+temp;
        JLabel balls=new JLabel(temp);
        balls.setFont(new Font("Serif",Font.BOLD,200));
        balls.setSize(1500,200);
        balls.setForeground(Color.WHITE);
        balls.setBackground(Color.BLACK);
        balls.setOpaque(true);

        gbc.gridx=0;
        gbc.gridy=0;
        jp_balls.add(jl_balls,gbc);
        gbc.gridy=1;
        jp_balls.add(balls,gbc);
////

/////
        JPanel jp_rr=new JPanel(new GridBagLayout());

        JLabel jl_rr=new JLabel("RUN RATE");
        jl_rr.setBackground(Color.WHITE);
        jl_rr.setBackground(Color.BLACK);
        jl_rr.setOpaque(false);
        jl_rr.setFont(new Font("Serif",Font.BOLD,30));
        jl_rr.setSize(1500,100);

        temp=String.format("%.01f", 6.0*Driver.score/(float)Math.max(1,Driver.totalBalls));
        while(temp.length()<5)temp=" "+temp;
        JLabel runRate=new JLabel(temp);
        runRate.setFont(new Font("Serif",Font.BOLD,200));
        runRate.setSize(1500,200);
        runRate.setForeground(Color.WHITE);
        runRate.setBackground(Color.BLACK);
        runRate.setOpaque(true);

        gbc.gridx=0;
        gbc.gridy=0;
        jp_rr.add(jl_rr,gbc);
        gbc.gridy=1;
        jp_rr.add(runRate,gbc);
////

        JPanel jp_overs_rr=new JPanel(new GridBagLayout());
        gbc.gridx=0;
        gbc.gridy=0;
        jp_overs_rr.add(jp_balls,gbc);
        gbc.gridy=1;
        jp_overs_rr.add(jp_rr,gbc);

        JPanel jp_score_overs_rr=new JPanel(new GridBagLayout());
        gbc.gridx=0;
        gbc.gridy=0;
        jp_score_overs_rr.add(jp_score_wickets,gbc);
        gbc.gridx=1;
        jp_score_overs_rr.add(jp_overs_rr,gbc);

        JPanel jp_striker_non=new JPanel(new GridBagLayout());
        gbc.gridx=0;
        gbc.gridy=0;
        JLabel temp=new JLabel(Driver.striker+" * "+Driver.strikerScore+" || "+Driver.nonStriker+" "+Driver.nonStrikerScore+" ");
        temp.setFont(new Font("Serif",Font.BOLD,100));
        jp_striker_non.add(temp,gbc);

        gbc.gridx=0;
        gbc.gridy=0;
        scorePanel.add(jp_score_overs_rr,gbc);
        gbc.gridy=1;
        scorePanel.add(jp_striker_non,gbc);


        if(Driver.chasing){
            JPanel chasing=new JPanel(new GridBagLayout());
            gbc.gridx=0;
            gbc.gridy=0;
            temp=new JLabel("Target: "+Driver.target+" || Required RR: "+String.format("%.01f",6*(Driver.target-Driver.score)/(6.0*Driver.NO_OF_OVERS-Driver.totalBalls)));
            temp.setFont(new Font("Serif",Font.BOLD,100));
            chasing.add(temp,gbc);

            gbc.gridx=0;
            gbc.gridy=1;
            temp=new JLabel("Need "+(Driver.target-Driver.score)+" from "+(6*Driver.NO_OF_OVERS-Driver.totalBalls)+" balls.");
            temp.setFont(new Font("Serif",Font.BOLD,100));
            chasing.add(temp,gbc);



            gbc.gridy=2;
            scorePanel.add(chasing,gbc);
        }

        scoreFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        scoreFrame.setContentPane(scorePanel);
        scoreFrame.pack();
        scorePanel.setVisible(true);
        scoreFrame.setVisible(true);
    }

    public static void disposeGUI(){
        scoreFrame.dispose();
        scoreFrame=new JFrame();
    }




}
