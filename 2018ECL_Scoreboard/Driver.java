import java.util.Scanner;

public class Driver {
    static int score=0;
    static int wickets=0;
    static int totalBalls=0;

    static int NO_OF_BATSMEN=11;
    static int NO_OF_OVERS=6;
    static Scanner sc=new Scanner(System.in);

    static String striker="";
    static String nonStriker="";
    static int strikerScore=0;
    static int nonStrikerScore=0;

    static boolean chasing=false;
    static int target=0;

    public static void main(String[] args) {
        System.out.println("No of batsmen: ");
        NO_OF_BATSMEN=sc.nextInt();
        System.out.println("No of overs: ");
        NO_OF_OVERS=sc.nextInt();

        System.out.println("Chasing: ");
        target=sc.nextInt();
        if(target>0)chasing=true;



        ControlPanel.buildGUI();
        ScorePanel.buildGUI();
    }

    public static void dotBall(){
        ControlPanel.balls.setValue((int)ControlPanel.balls.getValue()+1);

    }

    public static void runsForStriker(int runs){
        int strikerIndex=-1;
        for(int x=0;x<Driver.NO_OF_BATSMEN;x++) {
            if (ControlPanel.striker[x].isSelected()) {
                strikerIndex = x;
            }
        }
        System.out.print("runs"+runs);
        ControlPanel.scores[strikerIndex].setValue(((int)(ControlPanel.scores[strikerIndex].getValue()))+runs);
    }

    public static void swapBatsmen(){
        int strikerIndex=-1;
        int nonStrikerIndex=-1;
        for(int x=0;x<Driver.NO_OF_BATSMEN;x++){
            if(ControlPanel.striker[x].isSelected()){
                strikerIndex=x;
            }
            if(ControlPanel.nonStriker[x].isSelected()){
                nonStrikerIndex=x;
            }
        }

        if(strikerIndex>-1 && nonStrikerIndex>-1){

            ControlPanel.striker[strikerIndex].setSelected(false);
            ControlPanel.striker[nonStrikerIndex].setSelected(true);
            ControlPanel.nonStriker[nonStrikerIndex].setSelected(false);
            ControlPanel.nonStriker[strikerIndex].setSelected(true);
        }

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

    }
}
