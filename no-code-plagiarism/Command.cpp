#include "Command.h"

//INITIAL CLASS
Command::Command() {}
Command::~Command() {}

//VAR_DECLARATION 1
CommandVarDeclaration::CommandVarDeclaration() {}
CommandVarDeclaration::~CommandVarDeclaration() {}

//VAR_INITIALIZATION 2
CommandVarInitialization::CommandVarInitialization(): varDeclarationId(-1), upDefined(false) {}
CommandVarInitialization::~CommandVarInitialization() {}

//VAR_DEFINITION 3
CommandVarDefinition::CommandVarDefinition(): varDeclarationId(-1) {}
CommandVarDefinition::~CommandVarDefinition() {}

//FUNC_DEFINITION 4
CommandFuncDefinition::CommandFuncDefinition() {}
CommandFuncDefinition::~CommandFuncDefinition() {}

//FUNC_EXECUTION 5
CommandFuncExecution::CommandFuncExecution() {}
CommandFuncExecution::~CommandFuncExecution() {}

//FUNC_EXECUTION 6
CommandFuncDeclaration::CommandFuncDeclaration() {}
CommandFuncDeclaration::~CommandFuncDeclaration() {}

//COMMAND_STATEMENT
CommandStatement::CommandStatement():loopEnded(false) {}
CommandStatement::~CommandStatement() {}

//STMT_FOR 7
CommandStatementFor::CommandStatementFor() { loopEnded=false; }
CommandStatementFor::~CommandStatementFor() {}

//STMT_WHILE 8
CommandStatementWhile::CommandStatementWhile() { loopEnded=false; }
CommandStatementWhile::~CommandStatementWhile() {}

//STMT_IF 9
CommandStatementIf::CommandStatementIf() { loopEnded=false; }
CommandStatementIf::~CommandStatementIf() {}

