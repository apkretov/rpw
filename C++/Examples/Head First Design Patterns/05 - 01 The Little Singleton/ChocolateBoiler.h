#pragma once

#pragma region The Chocolate Factory
/* Java
public class ChocolateBoiler {
	private boolean empty;
	private boolean boiled;

	public ChocolateBoiler() { // This code is only started when the boiler is empty!
		empty = true;
		boiled = false;
	}

	public void fill() {
		if (isEmpty()) { // To fill the boiler it must be empty, and, once it�s full, we set the empty and boiled flags.
			empty = false;
			boiled = false;
			// fill the boiler with a milk/chocolate mixture
		}
	}

	public void drain() {
		if (!isEmpty() && isBoiled()) { // To drain the boiler, it must be full (non empty) and also boiled.Once it is drained we set empty back to true.
			// drain the boiled milk and chocolate
			empty = true;
		}
	}

	public void boil() {
		if (!isEmpty() && !isBoiled()) { // To boil the mixture, the boiler has to be full and not already boiled.Once it�s boiled we set the boiled flag to true.
			// bring the contents to a boil
			boiled = true;
		}
	}

	public boolean isEmpty() { return empty; }
	public boolean isBoiled() { return boiled; }
}
*/
class ChocolateBoiler {
    bool empty;
    bool boiled;
public:
    ChocolateBoiler() { // This code is only started when the boiler is empty!
        empty = true;
        boiled = false;
    }

    void fill() {
        if (isEmpty()) { // To fill the boiler it must be empty, and, once it's full, we set the empty and boiled flags.
            empty = false;
            boiled = false;
            // fill the boiler with a milk/chocolate mixture
        }
    }

    void drain() {
        if (!isEmpty() && isBoiled()) { // To drain the boiler, it must be full (non empty) and also boiled.Once it is drained we set empty back to true.
            // drain the boiled milk and chocolate
            empty = true;
        }
    }

    void boil() {
        if (!isEmpty() && !isBoiled()) { // To boil the mixture, the boiler has to be full and not already boiled.Once it's boiled we set the boiled flag to true.
            // bring the contents to a boil
            boiled = true;
        }
    }

    bool isEmpty() const { return empty; }
    bool isBoiled() const { return boiled; }
};
#pragma endregion //The Chocolate Factory
