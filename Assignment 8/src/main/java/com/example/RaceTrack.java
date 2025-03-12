package main.java.com.example;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import java.util.Random;

/* Create a class RaceTrack which uses JavaFX* (subclasses the Application class) and 
overrides its start method to do the required drawing. Each car must be advanced by a separate Thread. 
On each thread iteration, each car should advance a random 0-10 pixels forward. 
Once advanced, a thread should sleep for 50 miliseconds. 
The threads will execute until a car reaches the end of the track. 
Once this occurs, an Alert should be spawned alerting the user of the winner and all cars stop. 
The primaryStage will be 500px by 200px and is not be resizable. 

Please make the filepath for the car image a constant defined at 
the beginning of your RactTrack.java file so I can easily modify it for grading. 
(Or leave a comment indicating that the image path is a working web URL instead) 

HINT: Updating the GUI from a non-GUI thread is considered bad practice 
as it leads to race conditions and UI errors. 
If you need to update a GUI component from a non-GUI thread, 
please use the runLater method defined in the Platform class; 
only update the GUI with runLater (it will spin off its own thread). 
Don’t be dissuaded by the future time a runnable object passed to runLater will be executed. 
We can expect that any runnable object passed to runLater will be executed quickly enough for the purposes of this project.  */

public class RaceTrack extends Application {

    // Define the filepath for the car image
    private static String CAR_IMAGE_PATH = "C:/Users/Ramon/Pictures/how-to-create-a-car-NewBlogCover.png";

    // Width and height of the primaryStage
    private static int SCENE_WIDTH = 500;
    private static int SCENE_HEIGHT = 200;

    // Width and height of the cars
    private static int CAR_WIDTH = 50;
    private static int CAR_HEIGHT = 30;

    // The finish line position
    private static int FINISH_LINE = SCENE_WIDTH - CAR_WIDTH;

    // Number of cars in the race
    private static int NUM_CARS = 3;

    // Array to store the ImageView of each car
    private ImageView[] carImageViews;

    // Array to store the positions of each car
    private int[] carPositions;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Initialize the arrays
        carImageViews = new ImageView[NUM_CARS];
        carPositions = new int[NUM_CARS];

        // Create the Pane for the race track
        Pane raceTrackPane = new Pane();

        // Create and add cars to the race track
        for (int i = 0; i < NUM_CARS; i++) {
            carImageViews[i] = createCarImageView();
            carPositions[i] = 0;
            raceTrackPane.getChildren().add(carImageViews[i]);
        }

        // Set up the scene
        Scene scene = new Scene(raceTrackPane, SCENE_WIDTH, SCENE_HEIGHT);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Race Track");
        primaryStage.setResizable(false);

        // Show the primaryStage
        primaryStage.show();

        // Start the threads for each car
        for (int i = 0; i < NUM_CARS; i++) {
            int carIndex = i;
            new Thread(() -> raceCar(carIndex)).start();
        }
    }

    private ImageView createCarImageView() {
        Image carImage = new Image(CAR_IMAGE_PATH);
        ImageView imageView = new ImageView(carImage);
        imageView.setFitWidth(CAR_WIDTH);
        imageView.setFitHeight(CAR_HEIGHT);
        return imageView;
    }

    private void raceCar(int carIndex) {
        while (carPositions[carIndex] < FINISH_LINE) {
            // Advance the car by a random distance (0-10 pixels)
            int distance = new Random().nextInt(11);
            carPositions[carIndex] += distance;

            // Update the GUI using runLater to avoid UI thread issues
            Platform.runLater(() -> {
                carImageViews[carIndex].setTranslateX(carPositions[carIndex]);
            });

            try {
                // Sleep for 50 milliseconds
                Thread.sleep(50);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // If a car reaches the finish line, display a winner alert
        Platform.runLater(() -> {
            displayWinnerAlert(carIndex);
        });
    }

    private void displayWinnerAlert(int winnerIndex) {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("Race Over");
        alert.setHeaderText(null);
        alert.setContentText("Car " + (winnerIndex + 1) + " is the winner!");

        // Stop the application after the alert is closed
        alert.setOnHidden(event -> Platform.exit());

        alert.showAndWait();
    }
}