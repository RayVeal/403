package main.java.com.example;

import java.util.Random;

/* FoodProducer will have a single instance variable named bank of type FoodBank. 
FoodProducer will have a parameterized constructor with a single parameter of type FoodBank. 
The parameterized constructor will initialize the value of bank to the single parameter. 
FoodProducer will extend the Thread class and override Thread’s run method. 
FoodProducer’s run method will loop infinitely. 
On each loop iteration run will generate a random number from 1-100 and add that much food to the bank instance variable. 
After adding food, the thread will sleep for 100 milliseconds. */

public class FoodProducer extends Thread {
    private FoodBank bank;

    public FoodProducer(FoodBank bank) {
        this.bank = bank;
    }

    /* Thread.UncaughtExceptionHandler h = new Thread.UncaughtExceptionHandler() {
        @Override
        public void uncaughtException(Thread th, Throwable ex) {
            System.out.println("Uncaught exception: " + ex);
        }
    }; */

    @Override
    public void run() {
        Random random = new Random();

        while (true) {
            int amount = random.nextInt(100) + 1;
            bank.giveFood(amount);

            try {
                Thread.sleep(100);
            }  catch (InterruptedException e) {
                System.out.println("Interrupted.");
                System.out.println("Throwing exception ...");
                throw new RuntimeException();
            }
        }
    }
}
