import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonListeners implements ActionListener {
    public void actionPerformed(ActionEvent e){
        if(e.getSource().equals(ControlPanel.swapBatsmen)){
            Driver.swapBatsmen();

        }

        if(e.getSource().equals(ControlPanel.dotBall)){
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.oneRun)){
            Driver.runsForStriker(1);
            Driver.dotBall();
            Driver.swapBatsmen();
        }
        if(e.getSource().equals(ControlPanel.twoRuns)){
            Driver.runsForStriker(2);
            Driver.dotBall();

        }
        if(e.getSource().equals(ControlPanel.threeRuns)){
            Driver.runsForStriker(3);
            Driver.swapBatsmen();
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.four)){
            Driver.runsForStriker(4);
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.six)){
            Driver.runsForStriker(6);
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.extraOneNB)){
            ControlPanel.scores[Driver.NO_OF_BATSMEN].setValue((int)ControlPanel.scores[Driver.NO_OF_BATSMEN].getValue()+1);
            ControlPanel.balls.setValue((int)ControlPanel.balls.getValue()-1);
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.extraOne)){
            ControlPanel.scores[Driver.NO_OF_BATSMEN].setValue((int)ControlPanel.scores[Driver.NO_OF_BATSMEN].getValue()+1);
            Driver.dotBall();
        }

        if(e.getSource().equals(ControlPanel.extraOneSwap)){
            ControlPanel.scores[Driver.NO_OF_BATSMEN].setValue((int)ControlPanel.scores[Driver.NO_OF_BATSMEN].getValue()+1);
            Driver.swapBatsmen();
            Driver.dotBall();
        }



        UpdateScoreboard.ff();
    }
}
