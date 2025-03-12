package main.java.com.example;

/* Create a Java program that uses monitors to control access to a FoodBank object. 
FoodBank class that has a food amount and methods to give and take food. 
two Thread classes for this program that will 
either put food into the food bank or take food from the food bank. 
Food cannot be taken if there is no food available to take. 
This is not a true producer/consumer problem. 
You only have one condition, which is to wait if there is no food available to take. 
Both giving and taking food must involve locking the FoodBank object and unlocking it when done. 
The FoodBank object must never enter an invalid state (a negative amount of food) 
The methods in FoodBank to take and give food must print out exactly what is happening with each action in the method, 
i.e. “Waiting to get food”, “Taking 10 items of food, the balance is now 20 items”. 
NOTE: No other methods can print to the console. */

/* FoodBank will have a single instance variable named food of type int. 
FoodBank will define a default constructor which initializes food to zero. 
FoodBank will have two methods: giveFood and takeFood. Both methods will have a single parameter of type int. 
giveFood will add the value of the parameter to the food instance variable, takeFood will subtract the value.  */

public class FoodBank {
    private int food;

    public FoodBank() {
        this.food = 0;
    }

    public synchronized void giveFood(int amount) {
        if (amount < 0) {
            System.out.println("Invalid amount to give food");
            return;
        }

        food += amount;
        System.out.println("Giving " + amount + " items of food, the balance is now " + food + " items");
        notifyAll();
    }

    public synchronized void takeFood(int amount) {
        if (amount < 0) {
            System.out.println("Invalid amount to take food");
            return;
        }

        while (food < amount) {
            try {
                System.out.println("Waiting to get food");
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted.");
                System.out.println("Throwing exception ...");
                throw new RuntimeException();
            }
        }

        food -= amount;
        System.out.println("Taking " + amount + " items of food, the balance is now " + food + " items");
    }
}
