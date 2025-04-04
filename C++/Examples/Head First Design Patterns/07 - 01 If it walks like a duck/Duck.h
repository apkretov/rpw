#pragma once

#pragma region Its time to see an adapter in action //It's time to see an adapter in action
/* Java
public interface Duck { // This time around, our ducks implement a Duck interface that allows Ducks to quack and fly.
	public void quack();
	public void fly();
}
*/
class Duck { // This time around, our ducks implement a Duck interface that allows Ducks to quack and fly.
public:
	virtual ~Duck() = default;
	virtual void quack() = 0;
	virtual void fly() = 0;
};
#pragma endregion //Its time to see an adapter in action