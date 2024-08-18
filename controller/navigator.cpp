#include "navigator.h"
FSM_INITIAL_STATE(Screen, LoginScreen)



Navigator::Navigator(){}

void Navigator::navigateToSignUp()
{
    NavigatorDispatcher::dispatch(UserSignUp());
}

void Navigator::navigateToContactList()
{
    NavigatorDispatcher::dispatch(UserOpenContactList());
}

void Navigator::navigateToChat()
{
    NavigatorDispatcher::dispatch(UserChat());
}

void Navigator::navigateToPreviousPage()
{
    NavigatorDispatcher::dispatch(UserBack());
}

QString Navigator::screen() const
{
    return m_screen;
}

Navigator &Navigator::getInstance()
{
    static Navigator instance;
    return instance;
}

void Navigator::setScreen(QString screen)
{
    if (m_screen == screen)
        return;

    m_screen = screen;
    emit screenChanged(m_screen);
}



void LoginScreen::react(const UserSignUp &)
{
    transit<SignUpScreen>();
}

void LoginScreen::react(const UserOpenContactList &)
{
    transit<ContactListScreen>();
}

void LoginScreen::entry()
{
    //load login screen
    qDebug("load login screen");
    Navigator::getInstance().setScreen(Configuration::LoginScreen);
}



void SignUpScreen::react(const UserOpenContactList &)
{
    transit<ContactListScreen>();
}

void SignUpScreen::react(const UserBack &)
{
    transit<LoginScreen>();
}

void SignUpScreen::entry()
{
    //load sign up screen
    qDebug("load sign up screen");
    Navigator::getInstance().setScreen(Configuration::SignUpScreen);

}

void ContactListScreen::react(const UserChat &)
{
    transit<ChatScreen>();
}

void ContactListScreen::react(const UserBack &)
{
    transit<LoginScreen>();
}

void ContactListScreen::entry()
{
    //load ContactListScreen
    qDebug("load ContactListScreen");
    Navigator::getInstance().setScreen(Configuration::ContactListScreen);
}

void ChatScreen::react(const UserBack &)
{
    transit<ContactListScreen>();
}

void ChatScreen::entry()
{
    //load chat screen
    qDebug("load chat screen");
    Navigator::getInstance().setScreen(Configuration::ChatScreen);
}
