#pragma once

#pragma region Implementing the Command interface
/* Java
public interface Command{
	public void execute(); // Simple. All we need is one method called execute().
}
*/
class Command {
public:
	virtual ~Command() = default;
    virtual void execute() = 0; // Simple. All we need is one method called execute().
};
#pragma endregion //Implementing the Command interface