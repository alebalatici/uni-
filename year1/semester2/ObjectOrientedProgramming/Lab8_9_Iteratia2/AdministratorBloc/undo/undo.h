#ifndef ADMINISTRATORBLOC_UNDO_H
#define ADMINISTRATORBLOC_UNDO_H
#include <string>
#include "../domain/locatar.h"
#include "../repo/repo_locatari.h"

class ActiuneUndo {
    public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
    [[nodiscard]] virtual string get_undo_type() const = 0;
};

class UndoAdauga : public ActiuneUndo
{
    Repo& repo;
    Locatar locatar_adaugat;
    public:
    UndoAdauga(Repo& repository, const Locatar& loc) : repo{ repository }, locatar_adaugat{ loc } {};

    void doUndo() override
    {
        repo.delete_locatar(locatar_adaugat.get_apartment());
    }

    [[nodiscard]] string get_undo_type() const override
    {
       return "Undo Adauga";
    }
};

class UndoSterge : public ActiuneUndo
{
    Repo& repo;
    Locatar locatar_sters;
    public:
    UndoSterge(Repo& repository, const Locatar& loc) : repo{ repository }, locatar_sters{ loc } {};
    void doUndo() override
    {
        repo.add_locatar(locatar_sters);
    }

    [[nodiscard]] string get_undo_type() const override
    {
        return "Undo Sterge";
    }
};

class UndoModifica : public ActiuneUndo
{
    Repo& repo;
    Locatar locatar_modificat;

    public:
    UndoModifica(Repo& repository, const Locatar& loc) : repo { repository }, locatar_modificat { loc } {};

    [[nodiscard]] string get_undo_type() const override
    {
        return "Undo Modifica";
    }

    void doUndo() override
    {
        repo.delete_locatar(locatar_modificat.get_apartment());
        repo.add_locatar(locatar_modificat);
    }
};

#endif //ADMINISTRATORBLOC_UNDO_H
