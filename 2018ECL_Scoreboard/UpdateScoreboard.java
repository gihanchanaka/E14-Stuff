import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UpdateScoreboard implements ActionListener {
    public static void ff(){
        System.out.println("Updated");
        //ScorePanel.disposeGUI();

        Driver.score=0;
        for(int x=0;x<Driver.NO_OF_BATSMEN+1;x++)Driver.score+=(int)ControlPanel.scores[x].getValue();
        Driver.wickets=0;
        for(int x=0;x<Driver.NO_OF_OVERS+1;x++)Driver.wickets+=(int)ControlPanel.wickets[x].getValue();
        Driver.totalBalls=(int)ControlPanel.balls.getValue();


        for(int x=0;x<Driver.NO_OF_BATSMEN;x++){
            if(ControlPanel.striker[x].isSelected()){

                if(x==Driver.NO_OF_BATSMEN){
                    Driver.striker="";
                    Driver.strikerScore=0;
                }
                else{
                    Driver.striker=ControlPanel.batsmen[x].getText();
                    Driver.strikerScore=(int)ControlPanel.scores[x].getValue();

                }
            }

            if(ControlPanel.nonStriker[x].isSelected()){

                if(x==Driver.NO_OF_BATSMEN){
                    Driver.nonStriker="";
                    Driver.nonStrikerScore=0;
                }
                else{
                    Driver.nonStriker=ControlPanel.batsmen[x].getText();
                    Driver.nonStrikerScore=(int)ControlPanel.scores[x].getValue();

                }
            }
        }

        ScorePanel.buildGUI();
    }

    @Override
    public void actionPerformed(ActionEvent e){
        ff();
    }


}
