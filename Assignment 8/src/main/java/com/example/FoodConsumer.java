package main.java.com.example;

import java.util.Random;

/* FoodConsumer is identical to FoodProducer except that 
the random number generated in run will be removed from the FoodBank object.  */

public class FoodConsumer extends Thread {
    private FoodBank bank;

    public FoodConsumer(FoodBank bank) {
        this.bank = bank;
    }

    @Override
    public void run() {
        Random random = new Random();

        while (true) {
            int amount = random.nextInt(100) + 1;
            bank.takeFood(amount);

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                System.out.println("Interrupted.");
                System.out.println("Throwing exception ...");
                throw new RuntimeException();
            }
        }
    }
}
