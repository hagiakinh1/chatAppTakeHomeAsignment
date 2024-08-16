#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include <tinyfsm.hpp>
#include<config.h>
#include <QMap>
//Navigation is done using a state machine, each state is a screen.

//forward declaration
struct SignUpScreen;
struct ContactListScreen;
struct ChatScreen;


//events
struct UserLogin : tinyfsm::Event { };
struct UserSignUp : tinyfsm::Event { };
struct UserOpenContactList : tinyfsm::Event { };
struct UserChat : tinyfsm::Event { };
struct UserBack : tinyfsm::Event { };


//state
struct Screen : tinyfsm::Fsm<Screen>
{
    virtual void react(UserLogin const &) {};
    virtual void react(UserSignUp const &) {};
    virtual void react(UserOpenContactList const &) {};
    virtual void react(UserChat const &) {};
    virtual void react(UserBack const &) {};


  // alternative: enforce handling of Toggle in all states (pure virtual)
  //virtual void react(Toggle const &) = 0;

    virtual void entry(void) {};  /* entry actions in some states */
    void         exit(void)  {};  /* no exit actions */

  // alternative: enforce entry actions in all states (pure virtual)
  //virtual void entry(void) = 0;
};

struct LoginScreen:public Screen
{
    void react(UserSignUp const &)  ;
    void react(UserOpenContactList const &)  ;
    void react( const &)  ;
    void entry() override ;
};

struct SignUpScreen:public Screen
{
    void react(UserOpenContactList const &)  ; // sign up successfully
    void react(UserBack const &)  ; //user presses back button
    void entry() override ;
};

struct ContactListScreen:public Screen
{
    void react(UserChat const &)  ;
    void react(UserBack const &)  ; // user signs off
    void entry() override ;
};

struct ChatScreen:public Screen
{
    void react(UserBack const &)  ; //user presses back button
    void entry() override ;
};

using NavigatorDispatcher = Screen;

class Navigator: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString screen READ screen WRITE setScreen NOTIFY screenChanged)
    QString m_screen;


public:
    Q_INVOKABLE void navigateToSignUp();
    Q_INVOKABLE void navigateToContactList();
    Q_INVOKABLE void navigateToChat();
    Q_INVOKABLE void navigateToPreviousPage();
    QString screen() const;
    // Static method to get the singleton instance
    static Navigator& getInstance();

    // Delete copy constructor and assignment operator to prevent copying
    Navigator(const Navigator&) = delete;
    Navigator& operator=(const Navigator&) = delete;
    virtual ~Navigator() {}
public slots:
    void setScreen(QString screen);
signals:
    void screenChanged(QString screen);
private:
//    explicit Navigator(QObject * parent = nullptr);
    Navigator();
};

#endif // NAVIGATOR_H
