#pragma once

#pragma region Now its time to meet the newest fowl on the block //Now it's time to meet the newest fowl on the block
/* Java
public interface Turkey{
	public void gobble(); // Turkeys don't quack, they gobble.
	public void fly(); // Turkeys can fly, although they can only fly short distances.
}
*/
class Turkey {
public:
    virtual ~Turkey() = default;
    virtual void gobble() = 0; // Turkeys don't quack, they gobble.
    virtual void fly() = 0; // Turkeys can fly, although they can only fly short distances.
};
#pragma endregion //Now its time to meet the newest fowl on the block
