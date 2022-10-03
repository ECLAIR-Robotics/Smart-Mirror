package datastructures;

public class Main {

    public static void main(String[] args) {

        // Test Case 0
        Stack s = new Stack(10);

        for (int i = 0; i < 10; i++) {
            s.put(i);
        }

        assert s.peek() == 9;

        for (int i = 9; i >= 0; i--) {
            int out = s.pop(i);
            assert i == out;
        }

        // Insert Test Cases Here
    }
}
