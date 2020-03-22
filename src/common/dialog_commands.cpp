#include "dialog_commands.hpp"

//define available commands for every phase
const PhaseCommands DialogCommands::LoadUnloadButtons[CountPhases<PhasesLoadUnload>()] = {
    {},                                         //_init
    {},                                         //Parking
    {},                                         //WaitingTemp,
    {},                                         //PreparingToRam,
    {},                                         //Ramming,
    {},                                         //Unloading,
    {},                                         //Unloading2,
    { Command::CONTINUE },                      //UserPush,
    { Command::REHEAT },                        //NozzleTimeout,
    {},                                         //MakeSureInserted,
    {},                                         //Inserting,
    {},                                         //Loading,
    {},                                         //Purging,
    {},                                         //Purging2,
    { Command::CONTINUE, Command::PURGE_MORE }, //IsColor,
    {},                                         //Purging3,
};

const PhaseCommands DialogCommands::TestButtons[CountPhases<PhasesTest>()] = {
    {},
    {},
    {}
};
