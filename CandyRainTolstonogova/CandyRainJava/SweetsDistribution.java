public class SweetsDistribution {
    private int countCandy;
    private int countCake;
    private int countDonut;
    private int countTrash;
    
    public static final int FIX_COUNT = 9;
    public static final int MAX_COUNT = 30;
    
    public SweetsDistribution() {
        countCandyChoice();
        countCakeChoice();
        countDonutChoice();
        countTrashChoice();
    }
    
    public int countCandyChoice() {
        countCandy = (int)(Math.random() * FIX_COUNT) + 1;
        System.out.println("Количество конфет выбрано: " + countCandy);
        return countCandy;
    }
    
    public int countCakeChoice() {
        countCake = (int)(Math.random() * FIX_COUNT) + 1;
        System.out.println("Количество тортов выбрано: " + countCake);
        return countCake;
    }
    
    public int countDonutChoice() {
        countDonut = (int)(Math.random() * FIX_COUNT) + 1;
        System.out.println("Количество пончиков выбрано: " + countDonut);
        return countDonut;
    }
    
    public int countTrashChoice() {
        countTrash = MAX_COUNT - (countCandy + countCake + countDonut);
        System.out.println("Количество мусора загружено: " + countTrash);
        return countTrash;
    }
    
    // Getters and Setters
    public int getCountCandy() { return countCandy; }
    public int getCountCake() { return countCake; }
    public int getCountDonut() { return countDonut; }
    public int getCountTrash() { return countTrash; }
    public void setCountCandy(int count) { this.countCandy = count; }
    public void setCountCake(int count) { this.countCake = count; }
    public void setCountDonut(int count) { this.countDonut = count; }
    public void setCountTrash(int count) { this.countTrash = count; }
}