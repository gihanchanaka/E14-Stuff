import oracle.jrockit.jfr.JFR;

import javax.swing.*;
import java.awt.*;

public class ControlPanel {
    /*static JSpinner score=new JSpinner();
    static JSpinner wickets=new JSpinner();
    static JSpinner balls=new JSpinner();
    */
    static JTextArea[] batsmen=new JTextArea[Driver.NO_OF_BATSMEN+1];
    static JSpinner[] scores=new JSpinner[Driver.NO_OF_BATSMEN+1];
    static JTextArea[] bowlers=new JTextArea[Driver.NO_OF_OVERS+1];
    static JSpinner[] wickets=new JSpinner[Driver.NO_OF_OVERS+1];

    static JRadioButton[] striker=new JRadioButton[Driver.NO_OF_BATSMEN+1];
    static JRadioButton[] nonStriker=new JRadioButton[Driver.NO_OF_BATSMEN+1];

    static JSpinner balls=new JSpinner();


    static JButton swapBatsmen,dotBall,oneRun,twoRuns,threeRuns,four,six,extraOneNB,extraOne,extraOneNBSwap,extraOneSwap;

    public static void buildGUI(){
        JFrame controlFrame=new JFrame("Control panel");
        JPanel controlPanel=new JPanel();

        controlPanel.setLayout(new GridBagLayout());
        controlPanel.setPreferredSize(new Dimension(1200,800));

        GridBagConstraints gbc=new GridBagConstraints();
        gbc.ipadx=10;
        ButtonGroup strikers_group = new ButtonGroup();
        ButtonGroup nonstrikers_group = new ButtonGroup();

        gbc.gridy=0;
        gbc.gridx=1;controlPanel.add(new JLabel("Striker"),gbc);
        gbc.gridx=2;controlPanel.add(new JLabel("Non striker"),gbc);
        gbc.gridx=3;controlPanel.add(new JLabel("Batsman name"),gbc);
        gbc.gridx=4;controlPanel.add(new JLabel("Runs"),gbc);
        gbc.gridx=7;controlPanel.add(new JLabel("Bowler name"),gbc);
        gbc.gridx=8;controlPanel.add(new JLabel("Wickets"),gbc);

        for(int y=0;y<Driver.NO_OF_BATSMEN+1;y++){
            gbc.gridy=y+1;
            striker[y]=new JRadioButton();
            nonStriker[y]=new JRadioButton();
            gbc.gridx=1;
            controlPanel.add(striker[y],gbc);
            strikers_group.add(striker[y]);
            gbc.gridx=2;
            controlPanel.add(nonStriker[y],gbc);
            nonstrikers_group.add(nonStriker[y]);
        }


        for(int y=0;y<Driver.NO_OF_BATSMEN+1;y++){
            gbc.gridy=y+1;
            gbc.gridx=3;
            if(y<Driver.NO_OF_BATSMEN){batsmen[y]=new JTextArea("Batsman "+(y+1));
            }
            else{
                batsmen[y]=new JTextArea("Extras :  ");
                batsmen[y].setEditable(false);
            }
            controlPanel.add(batsmen[y],gbc);

            gbc.gridx=4;
            scores[y]=new JSpinner();
            controlPanel.add(scores[y],gbc);
        }


        for(int y=0;y<Driver.NO_OF_OVERS+1;y++){
            gbc.gridy=y+1;
            gbc.gridx=7;
            if(y<Driver.NO_OF_OVERS)bowlers[y]=new JTextArea("Bowler "+(y+1));

            else{
                bowlers[y]=new JTextArea("Runouts :  ");
                bowlers[y].setEditable(false);
            }
            controlPanel.add(bowlers[y],gbc);

            gbc.gridx=8;
            wickets[y]=new JSpinner();
            controlPanel.add(wickets[y],gbc);
        }


        gbc.gridy=7;
        gbc.gridx=10;
        controlPanel.add(new JLabel("Balls: "),gbc);

        gbc.gridx=11;
        controlPanel.add(balls,gbc);


        JButton updateScoreBoard=new JButton("Update");
        updateScoreBoard.addActionListener(new UpdateScoreboard());
        gbc.gridx=5;
        gbc.gridy=15;
        controlPanel.add(updateScoreBoard,gbc);

        gbc.gridy=20;
        gbc.gridx=0;

        swapBatsmen=new JButton("Swap batsmen");
        swapBatsmen.addActionListener(new ButtonListeners());
        controlPanel.add(swapBatsmen,gbc);

        gbc.gridx=1;
        dotBall=new JButton("0");
        dotBall.addActionListener(new ButtonListeners());
        controlPanel.add(dotBall,gbc);


        gbc.gridx=2;
        oneRun=new JButton("1");
        oneRun.addActionListener(new ButtonListeners());
        controlPanel.add(oneRun,gbc);

        gbc.gridx=3;
        twoRuns=new JButton("2");
        twoRuns.addActionListener(new ButtonListeners());
        controlPanel.add(twoRuns,gbc);

        gbc.gridx=4;
        threeRuns=new JButton("3");
        threeRuns.addActionListener(new ButtonListeners());
        controlPanel.add(threeRuns,gbc);


        gbc.gridx=5;
        four=new JButton("4!");
        four.addActionListener(new ButtonListeners());
        controlPanel.add(four,gbc);


        gbc.gridx=6;
        six=new JButton("6!");
        six.addActionListener(new ButtonListeners());
        controlPanel.add(six,gbc);

        gbc.gridx=7;
        extraOneNB=new JButton("extraOneNB");
        extraOneNB.addActionListener(new ButtonListeners());
        controlPanel.add(extraOneNB,gbc);

        gbc.gridx=8;
        extraOne=new JButton("extraOne");
        extraOne.addActionListener(new ButtonListeners());
        controlPanel.add(extraOne,gbc);

        gbc.gridx=9;
        extraOneSwap=new JButton("extraOneSwap");
        extraOneSwap.addActionListener(new ButtonListeners());
        controlPanel.add(extraOneSwap,gbc);


        controlFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        controlFrame.setContentPane(controlPanel);
        controlFrame.pack();
//        controlPanel.setVisible(true);
        controlFrame.setVisible(true);

    }

    /*public static void buildGUI2(){
        JFrame controlFrame=new JFrame("Control panel");
        JPanel controlPanel=new JPanel();

        controlPanel.setLayout(new GridLayout(8,2));
        controlPanel.setPreferredSize(new Dimension(400,400));

        GridBagConstraints gbc=new GridBagConstraints();

        gbc.gridx=0;
        gbc.gridy=0;
        controlPanel.add(new JLabel("Score: "),gbc);
        gbc.gridx=0;
        gbc.gridy=1;
        score.setValue(Driver.score);
        controlPanel.add(score,gbc);

        gbc.gridx=1;
        gbc.gridy=0;
        controlPanel.add(new JLabel("Wickets: "),gbc);
        gbc.gridx=1;
        gbc.gridy=1;
        wickets.setValue(Driver.wickets);
        controlPanel.add(wickets,gbc);

        gbc.gridx=2;
        gbc.gridy=0;
        controlPanel.add(new JLabel("Balls: "),gbc);
        gbc.gridx=2;
        gbc.gridy=1;
        balls.setValue(Driver.totalBalls);
        controlPanel.add(balls,gbc);


        JButton updateScoreBoard=new JButton("Update");
        updateScoreBoard.addActionListener(new UpdateScoreboard());
        gbc.gridx=0;
        gbc.gridy=0;
        controlPanel.add(updateScoreBoard,gbc);

        controlFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        controlFrame.setContentPane(controlPanel);
        controlFrame.pack();
        controlPanel.setVisible(true);
        controlFrame.setVisible(true);



    }*/

}
