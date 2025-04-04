#pragma once

#pragma region 1 When commands support undo
/* Java
public interface Command{
	public void execute();
	public void undo(); // Here's the new undo() method.
}
*/
class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
	virtual void undo() = 0; // Here's the new undo() method.
};
#pragma endregion //1 When commands support undo