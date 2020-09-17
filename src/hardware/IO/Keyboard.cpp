
#include "Keyboard.h"

Keyboard::Keyboard() {
    std::cout << "Keyboard object created, echo disabled" << std::endl;
    keyboardActive = NB_DISABLE;
    nonblock(NB_ENABLE);
    /* obtain the current terminal configuration */
    tcgetattr(STDIN_FILENO, &original);
    /* duplicate it */
    noecho = original;
    /* turn off full duplex */
    noecho.c_lflag = noecho.c_lflag ^ ECHO;
    /* set the terminal */
    tcsetattr(STDIN_FILENO, TCSANOW, &noecho);
}
Keyboard::~Keyboard() {
    /* restore the terminal settings */
    std::cout << "Keyboard object deleted, echo enabled" << std::endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
};
void Keyboard::updateInput() {
    // usleep(1);
    clearCurrentStates();
    setKeyboardActive(kbhit());
    if (getKeyboardActive() != 0) {
        setKeys();
        //printPressed();
    }
}
void Keyboard::setKeys() {
    /// set last Key states
    char ch = fgetc(stdin);
    /* Set States, limited to one key Press at a time*/

    switch (ch) {
        case 'a':
        case 'A':
            currentKeyStates.a = true;
            break;
        case 's':
        case 'S':
            currentKeyStates.s = true;
            break;
        case 'e':
        case 'E':
            currentKeyStates.e = true;
            break;
        case 'd':
        case 'D':
            currentKeyStates.d = true;
            break;
        case 'w':
        case 'W':
            currentKeyStates.w = true;
            break;
        case 'x':
        case 'X':
            currentKeyStates.x = true;
            break;
        case 'r':
        case 'R':
            currentKeyStates.r = true;
            break;
        case 'q':
        case 'Q':
            currentKeyStates.q = true;
            std::cout << std::endl
                      << "Q PRESSED, EXITING PROGRAM "
                      << std::endl;
            break;
        case '+':
            currentKeyStates.plus = true;
            break;
        case '-':
            currentKeyStates.minus = true;
            break;
        case '\n':
            currentKeyStates.enter = true;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            currentKeyStates.number = ch;
            break;
        default:
            keyboardActive = 0;
    }
}
key_states Keyboard::getStates() {
    key_states current_state = {this->currentKeyStates.a, this->currentKeyStates.s,
                                this->currentKeyStates.d, this->currentKeyStates.w,
                                this->currentKeyStates.x, this->currentKeyStates.x,
                                this->currentKeyStates.e, this->currentKeyStates.r,
                                this->currentKeyStates.plus, this->currentKeyStates.minus,
                                this->currentKeyStates.enter, this->currentKeyStates.number};
    return current_state;
};
void Keyboard::printPressed() {
    if (getA()) {
        std::cout
            << "PRESSED A " << std::endl;
    }
    if (getS()) {
        std::cout
            << "PRESSED S " << std::endl;
    }
    if (getD()) {
        std::cout
            << "PRESSED D " << std::endl;
    }
    if (getE()) {
        std::cout
            << "PRESSED E " << std::endl;
    }
    if (getW()) {
        std::cout
            << "PRESSED W " << std::endl;
    }
    if (getX()) {
        std::cout
            << "PRESSED X " << std::endl;
    }
    if (getR()) {
        std::cout
            << "PRESSED R " << std::endl;
    }
    if (getPlus()) {
        std::cout
            << "PRESSED PLUS " << std::endl;
    }
    if (getMinus()) {
        std::cout
            << "PRESSED MINUS " << std::endl;
    }
    if (getEnter()) {
        std::cout
            << "PRESSED ENTER " << std::endl;
    }
    if (getNum()) {
        std::cout
            << "PRESSED A NUMBER " << std::endl;
    }
}
void Keyboard::clearCurrentStates() {
    currentKeyStates.a = false;
    currentKeyStates.s = false;
    currentKeyStates.e = false;
    currentKeyStates.d = false;
    currentKeyStates.w = false;
    currentKeyStates.x = false;
    currentKeyStates.r = false;
    currentKeyStates.plus = false;
    currentKeyStates.minus = false;
    currentKeyStates.enter = false;
    currentKeyStates.number = '\0';
}
bool Keyboard::getA() {
    return currentKeyStates.a;
};

bool Keyboard::getS() {
    return currentKeyStates.s;
};
bool Keyboard::getE() {
    return currentKeyStates.e;
};
bool Keyboard::getD() {
    return currentKeyStates.d;
};
bool Keyboard::getW() {
    return currentKeyStates.w;
};
bool Keyboard::getX() {
    return currentKeyStates.x;
};
bool Keyboard::getQ() {
    return currentKeyStates.q;
};
bool Keyboard::getR() {
    return currentKeyStates.r;
}
bool Keyboard::getPlus() {
    return currentKeyStates.plus;
};
bool Keyboard::getMinus() {
    return currentKeyStates.minus;
}
bool Keyboard::getEnter() {
    return currentKeyStates.enter;
}
char Keyboard::getNum() {
    return currentKeyStates.number;
}
int Keyboard::kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);  //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
void Keyboard::nonblock(int state) {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    } else if (state == NB_DISABLE) {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
int Keyboard::getKeyboardActive() {
    return keyboardActive;
};
void Keyboard::setKeyboardActive(int value) {
    keyboardActive = value;
};