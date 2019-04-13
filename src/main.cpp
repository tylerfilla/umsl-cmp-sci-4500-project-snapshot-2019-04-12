/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include <libgen.h>

#include "global.h"
#include "version.h"

/** Operations to perform. */
enum class Operation {
  nop = 0,
  list_friends,
  remove_friends,
  start_interactive,
};

/** A command-line command. */
struct Command {
  /** A command option. */
  struct Option {
    /** The option aliases. */
    std::initializer_list<std::string_view> aliases;

    /** The option description. */
    std::string_view description;

    /** True if the option is a flag, otherwise false. */
    bool is_flag;

    /** The option data key. */
    std::string_view data_key;
  };

  /** The command aliases. */
  std::initializer_list<std::string_view> aliases;

  /** The command long name. */
  std::string_view long_name;

  /** The command description. */
  std::string_view description;

  /** The command operation. */
  Operation operation;

  /** The command subcommands. */
  std::initializer_list<Command> subcommands;

  /** The command options. */
  std::initializer_list<Option> options;
};

/** The command layout. */
constexpr Command root_command {
  {}, // No aliases
  nullptr, // No long name
  nullptr, // No description
  Operation::nop,
  {
    Command {
      {"friend", "fr"},
      "friend",
      "friend management",
      Operation::nop,
      {
        Command {
          {"list", "ls"},
          "friend list",
          "list friend details",
          Operation::list_friends,
          {/* No subcommands */},
          {
            Command::Option {
              {"-f", "--fid"},
              "the friend id",
              false, // Not a flag
              "friend_id",
            },
          },
        },
        Command {
          {"remove", "rm"},
          "friend remove",
          "remove friends",
          Operation::remove_friends,
          {/* No subcommands */},
          {
            Command::Option {
              {"-f", "--fid"},
              "the friend id",
              false, // Not a flag
              "friend_id",
            },
          },
        },
      },
      {/* No options */},
    },
    Command {
      {"go"},
      "go",
      "start interactive use",
      Operation::start_interactive,
      {/* No subcommands */},
      {/* No options */},
    },
  },
  {
    Command::Option {
      {"-h", "--help"},
      "show help information",
      true, // Flag
      "help",
    },
    Command::Option {
      {"--legal"},
      "show legal information",
      true, // Flag
      "legal",
    },
    Command::Option {
      {"--version"},
      "show version information",
      true, // Flag
      "version",
    },
  },
};

/**
 * Print header text for a command to an output stream.
 *
 * @tparam OStream Type of the output stream
 * @param cmd The command
 * @param o The output stream
 */
template<class OStream>
void print_header(const Command& cmd, OStream&& o) {
  // The command string
  auto str = std::string(g->exec);

  // If command has a long name
  if (!cmd.long_name.empty()) {
    // Append long name
    str += " ";
    str += cmd.long_name;
  }

  // Print header text
  o << "usage: " << str << " <command> [<args>]\n"
    << "   or: " << str << " <opts>\n";
}

/**
 * Print help text for a command to an output stream.
 *
 * @tparam OStream Type of the output stream
 * @param cmd The command
 * @param o The output stream
 */
template<class OStream>
void print_help(const Command& cmd, OStream&& o) {
  print_header(cmd, o);

  // If command has options
  if (cmd.options.size()) {
    std::cout << "\n";
    std::cout << "options:\n";

    // The target padding between aliases and description
    int target_pad = 16;

    // Loop through subcommands for content
    for (auto&& opt : cmd.options) {
      std::cout << "  ";

      // Print aliases with separating commas
      int pad = 0;
      for (auto alias = opt.aliases.begin(); alias != opt.aliases.end(); ++alias) {
        std::cout << *alias;
        pad += alias->length();

        if (alias < opt.aliases.end() - 1) {
          std::cout << ", ";
          pad += 2;
        }
      }

      // Pad the space between aliases and description
      for (; pad < target_pad; ++pad) {
        std::cout << " ";
      }

      // Print description
      std::cout << opt.description;
      std::cout << "\n";
    }
  }

  // If command has subcommands
  if (cmd.subcommands.size()) {
    std::cout << "\n";
    std::cout << "commands:\n";

    // The target padding between aliases and description
    int target_pad = 16;

    // Loop through subcommands for content
    for (auto&& sub : cmd.subcommands) {
      std::cout << "  ";

      // Print aliases with separating commas
      int pad = 0;
      for (auto alias = sub.aliases.begin(); alias != sub.aliases.end(); ++alias) {
        std::cout << *alias;
        pad += alias->length();

        if (alias < sub.aliases.end() - 1) {
          std::cout << ", ";
          pad += 2;
        }
      }

      // Pad the space between aliases and description
      for (; pad < target_pad; ++pad) {
        std::cout << " ";
      }

      // Print description
      std::cout << sub.description;
      std::cout << "\n";
    }
  }
}

/**
 * Print usage text for a command to an output stream.
 *
 * @tparam OStream Type of the output stream
 * @param cmd The command
 * @param o The output stream
 */
template<class OStream>
void print_usage(const Command& cmd, OStream&& o) {
  print_header(cmd, o);

  // The command string
  auto str = std::string(g->exec);

  // If command has a long name
  if (!cmd.long_name.empty()) {
    // Append long name
    str += " ";
    str += cmd.long_name;
  }

  std::cout << "\n";
  o << "try `" << str << " -h' for more info\n";
}

/**
 * Print legal text to an output stream.
 *
 * @tparam OStream Type of the output stream
 * @param o The output stream
 */
template<class OStream>
void print_legal(OStream&& o) {
  o << "Cozmonaut\n"
    << "Copyright 2019 The Cozmonaut Contributors\n";
}

/**
 * Print version text to an output stream.
 *
 * @tparam OStream Type of the output stream
 * @param o The output stream
 */
template<class OStream>
void print_version(OStream&& o) {
  o << g->exec << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "\n"
    << "built on " << VERSION_TIMESTAMP << "\n"
    << "commit " << VERSION_VCS_HASH << " (" << VERSION_VCS_BRANCH << ")\n";
}

/**
 * Read command-line arguments.
 *
 * @return A pair with the command and a map of read data
 */
static std::pair<const Command&, std::unordered_map<std::string, std::string>> read_arguments() {
  // The read data map
  std::unordered_map<std::string, std::string> data;

  // A list of encountered command parts (the command chain)
  // The root command is implicitly encountered right out of the gate
  std::vector<std::reference_wrapper<const Command>> commands;
  commands.emplace_back(root_command);

  // Try to match an argument as an option
  auto match_option = [&](std::string_view arg) -> const Command::Option* {
    // Walk up the command chain in reverse
    for (auto command_it = commands.rbegin(); command_it != commands.rend(); ++command_it) {
      // The command under consideration
      auto& command = command_it->get();

      // Loop through known options on the command
      for (auto& param : command.options) {
        // If an alias matches the argument
        if (std::find(param.aliases.begin(), param.aliases.end(), arg) != param.aliases.end()) {
          // Return the parameter
          return &param;
        }
      }
    }

    return nullptr;
  };

  // Try to match an argument as a command
  auto match_subcommand = [&](std::string_view arg) -> const Command* {
    // The command under consideration
    // We do not walk the command chain for subcommands
    auto& command = commands.back().get();

    // Loop through known subcommands on the command
    for (auto& cmd : command.subcommands) {
      // If an alias matches the argument
      if (std::find(cmd.aliases.begin(), cmd.aliases.end(), arg) != cmd.aliases.end()) {
        // Return the command
        return &cmd;
      }
    }

    return nullptr;
  };

  // Loop through user-given arguments (skipping the first one)
  for (auto argi = g->argv + 1; argi != g->argv + g->argc; ++argi) {
    std::string_view arg = *argi;

    // Classify the argument
    if (arg.length() > 2 && arg.find("--") == 0) {
      // Argument starts with two dashes, so assume it is a GNU-style option

      // Split argument at the equal sign, if any
      auto arg_eq = arg.find_last_of('=');
      auto arg_eq_before = arg.substr(0, arg_eq);
      auto arg_eq_after = arg_eq == std::string_view::npos ? std::string_view() : arg.substr(arg_eq + 1);

      // Try to match it like an option
      if (auto param = match_option(arg_eq_before)) {
        // If parameter is a flag
        if (param->is_flag) {
          // If parameter has a data key
          if (!param->data_key.empty()) {
            // Set corresponding flag
            data[std::string(param->data_key)] = "true";
          }
        } else {
          // Parameter is not a flag
          // We need to grab more data from the user

          // If parameter has a data key
          if (!param->data_key.empty()) {
            // The parameter data
            std::string_view param_data;

            // Prefer to use data given after the equal sign
            if (!arg_eq_after.empty()) {
              param_data = arg_eq_after;
            } else {
              // If nothing is after the equal sign and all arguments are exhausted
              // This advances the argument iterator, and the for loop will do so again at "continue" below
              if (arg_eq_after.empty() && ++argi >= g->argv + g->argc) {
                // There is no way to get the data we need, so halt
                std::cerr << "no data given to long option: " << arg_eq_before << "\n";
                return {commands.back(), data};
              }

              // Use the next argument as raw data
              param_data = *argi;
            }

            // Map the data
            data[std::string(param->data_key)] = param_data;
          }
        }

        // Next argument
        continue;
      }

      std::cerr << "no such long option: " << arg << "\n";
      return {commands.back(), data};
    } else if (arg.length() > 1 && arg.find('-') == 0) {
      // Argument starts with one dash, so assume it is a POSIX-style option

      // Loop through characters in argument (skipping the dash)
      // This is needed as POSIX-style options can compound (e.g. -abc means -a -b -c)
      for (auto c : arg.substr(1)) {
        // Assemble a small string isolating this option
        char buf[3];
        buf[0] = '-';
        buf[1] = c;
        buf[2] = '\0';

        // Try to match it like an option
        if (auto param = match_option(buf)) {
          // If parameter is a flag
          if (param->is_flag) {
            // If parameter has a data key
            if (!param->data_key.empty()) {
              // Set corresponding flag
              data[std::string(param->data_key)] = "true";
            }
          } else {
            // Parameter is not a flag
            // We need to grab more data from the user

            // If parameter has a data key
            if (!param->data_key.empty()) {
              // This advances the argument iterator, and the for loop will do so again at "continue" below
              if (++argi >= g->argv + g->argc) {
                // There is no way to get the data we need, so halt
                std::cerr << "no data given to short option: " << buf << "\n";
                return {commands.back(), data};
              }

              // Map the data
              data[std::string(param->data_key)] = *argi;
            }
          }

          // Next option
          continue;
        }

        std::cerr << "no such short option: " << buf << "\n";
        return {commands.back(), data};
      }
    } else {
      // The argument is not an option, so assume it is a subcommand

      // Try to match it like a subcommand
      if (auto cmd = match_subcommand(arg)) {
        // Add subcommand to the chain
        commands.emplace_back(*cmd);

        // Next argument
        continue;
      }

      // Unrecognized argument
      std::cerr << "unrecognized argument: " << arg << "\n";
      return {commands.back(), data};
    }
  }

  // Return the final results
  return {commands.back(), data};
}

int main(int argc, const char** argv) {
  g_mut->argc = argc;
  g_mut->argv = argv;

  // Get the executable name
  g_mut->exec = ::strdup(::basename(const_cast<char*>(argv[0])));

  // Read command-line arguments
  auto&&[cmd, data] = read_arguments();

  // If help was requested
  if (data.find("help") != data.end()) {
    print_help(cmd, std::cout);
    return 0;
  }

  // If legal was requested
  if (data.find("legal") != data.end()) {
    print_legal(std::cout);
    return 0;
  }

  // If version was requested
  if (data.find("version") != data.end()) {
    print_version(std::cout);
    return 0;
  }

  // Dispatch requested operation
  switch (cmd.operation) {
    case Operation::nop:
      // No operation to perform, so show usage
      print_usage(cmd, std::cout);
      break;
    case Operation::list_friends:
      std::cout << "want to list friends: " << data["friend_id"] << "\n";
      break;
    case Operation::remove_friends:
      // If friend ID was not given, show usage
      if (data.find("friend_id") == data.end()) {
        std::cout << "no friend id provided\n" << "\n";
        print_usage(cmd, std::cout);
        return 0;
      }
      std::cout << "want to remove friends: " << data["friend_id"] << "\n";
      break;
    case Operation::start_interactive:
      std::cout << "want to start interactive\n";
      break;
  }
}
