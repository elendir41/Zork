#include "Command.h"

/**
 * Create a command object. First and second word must be supplied, but
 * either one (or both) can be null. The command word should be null to
 * indicate that this was a command that is not recognised by this game.
 */
Command::Command(QString firstWord, QString secondWord) {
	this->commandWord = firstWord;
	this->secondWord = secondWord;
}

/**
 * Return the command word (the first word) of this command. If the
 * command was not understood, the result is null.
 */
QString Command::getCommandWord() {
	return this->commandWord;
}

/**
 * Return the second word of this command. Returns null if there was no
 * second word.
 */
QString Command::getSecondWord() {
	return this->secondWord;
}

/**
 * Return true if this command was not understood.
 */
bool Command::isUnknown() {
    return (commandWord.isEmpty());
}

/**
 * Return true if the command has a second word.
 */
bool Command::hasSecondWord() {
    return (!secondWord.isEmpty());
}

