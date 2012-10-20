#ifndef SESSION_H
#define SESSION_H

#include <QMetaType>
#include <QObject>


class Player;
class Realm;

class Session : public QObject {

    Q_OBJECT

    public:
        enum SignInStage {
            SessionClosed = 0,
            AskingUserName,
            AskingUserNameConfirmation,
            AskingPassword,
            AskingSignupPassword,
            AskingSignupPasswordConfirmation,
            AskingGender,
            AskingSignupConfirmation,
            SignedIn,
            SignInAborted
        };

        Session(Realm *realm, const QString &source, QObject *parent);
        virtual ~Session();

        void open();

        SignInStage signInStage() const { return m_signInStage; }
        bool authenticated() const { return m_signInStage == SignedIn; }

        Player *player() const { return m_player; }

        void processSignIn(const QString &data);

        void signOut();

    public slots:
        void onUserInput(QString data);

    signals:
        void write(const QString &data);

        void terminate();

    private:
        QString m_source;

        SignInStage m_signInStage;

        struct SignUpData;
        SignUpData *m_signUpData;

        Realm *m_realm;
        Player *m_player;

        void setSignInStage(SignInStage signInStage);

        void startAskingUserName();
        void askForUserName();
        void processUserName(const QString &answer);

        void startAskingUserNameConfirmation();
        void askForUserNameConfirmation();
        void processUserNameConfirmation(const QString &answer);

        void startAskingPassword();
        void askForPassword();
        void processPassword(const QString &input);

        void startAskingSignupPassword();
        void askForSignupPassword();
        void processSignupPassword(const QString &input);

        void startAskingSignupPasswordConfirmation();
        void askForSignupPasswordConfirmation();
        void processSignupPasswordConfirmation(const QString &input);

        void startAskingGender();
        void askForGender();
        void processGender(const QString &answer);

        void startAskingSignupConfirmation();
        void askForSignupConfirmation();
        void processSignupConfirmation(const QString &answer);

        void showColumns(const QStringList &items);
};

Q_DECLARE_METATYPE(Session *)

#endif // SESSION_H
