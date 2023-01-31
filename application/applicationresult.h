#ifndef APPLICATIONRESULT_H
#define APPLICATIONRESULT_H

#include <searchresult.h>

class ApplicationResult : public SearchResult
{
    Q_OBJECT
public:
    explicit ApplicationResult(QObject *parent = nullptr);
    ApplicationResult(const QString& name, const QString& context, int imageIndex, QObject *parent = nullptr);

    virtual QString delegate() const override;
    virtual QString imagePath() const override;
    Q_INVOKABLE void run() const;
    Q_INVOKABLE void runPrivileged() const;
private:
    int imageIndex_;
};

Q_DECLARE_METATYPE(ApplicationResult)

#endif // APPLICATIONRESULT_H
