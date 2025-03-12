package main.java.com.example;

/* FoodBankPatrons will have a main method in which a FoodBank, FoodProducer, and FoodConsumer object are created. 
The FoodProducer and FoodConsumer must share the same FoodBank object. 
Once created, the main method starts these threads. */

public class FoodBankPatrons {
    public static void main(String[] args) {
        FoodBank foodBank = new FoodBank();
        FoodProducer producer = new FoodProducer(foodBank);
        FoodConsumer consumer = new FoodConsumer(foodBank);

        producer.start();
        consumer.start();
    }
}
