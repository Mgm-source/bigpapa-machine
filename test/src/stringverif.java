
public class stringverif {
// private variables 
    private char[] container;
    private int stringnum = 0;
    private int intStringnum = 0;

// methods 
    public void takeString(String s)
        {
            container = new char[s.length()]; 

             for (int i = 0; i < s.length(); i++) { 
                container[i] = s.charAt(i); 
             }
        }

    public void sorter() {

        for (char c : container) {
            if(Character.isDigit(c)){
                intStringnum++;
    
            }
            if (Character.isLowerCase(c))
            {
                stringnum++;
            }
            
        }
        
    }

    public String getterString()
        {
            if (intStringnum>stringnum)
            {
                return "numbers";
            }
            if (stringnum>intStringnum)
            {
                return "letters";
            }
            return "even";
        }
}

