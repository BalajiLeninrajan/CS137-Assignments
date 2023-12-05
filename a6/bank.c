#include "bank.h"

Bank *CreateBank(double money, double maxLoan,
                 double loanInterest, double transferFeeRate)
{
    // Allocate bank
    Bank *bank = malloc(sizeof(Bank));
    assert(bank);
    // No accounts yet
    bank->accounts = NULL;
    bank->nAcc = 0;
    // Assign inputs
    bank->money = money;
    bank->maxLoan = maxLoan;
    bank->loanInterest = loanInterest;
    bank->transferFeeRate = transferFeeRate;

    return bank;
}

Account *OpenAccount(Bank *bank)
{
    bank->nAcc++;

    // Account Info
    Account *newAccount = malloc(sizeof(Account));
    newAccount->id = bank->nAcc;
    newAccount->active = true;
    newAccount->balance = 0;

    // Loan info
    Loan newLoan;
    newLoan.active = false;
    newLoan.amount = 0;
    newLoan.interest = 1;
    newAccount->loan = newLoan;

    // Pointer to Bank
    newAccount->bank = bank;

    // Append newAccount to bank
    bank->accounts = realloc(bank->accounts, sizeof(Account) * bank->nAcc);
    bank->accounts[bank->nAcc - 1] = newAccount;

    return newAccount;
}

void Deposit(double amount, Account *account)
{
    if (account->active)
    {
        account->balance += amount;
    }
}

bool Withdraw(double amount, Account *account)
{
    if (account->active && account->balance >= amount)
    {
        account->balance -= amount;
        return true;
    }
    return false;
}

bool TakeLoan(double amount, Account *account)
{
    // account inactive
    if (account->loan.active || !account->active)
    {
        return false;
    }

    // Bank lacks funds
    if (account->bank->maxLoan < amount || account->bank->money < amount)
    {
        return false;
    }

    // update account, loan and bank
    account->balance += amount;
    account->bank->money -= amount;
    account->loan.active = true;
    account->loan.amount = amount;
    account->loan.interest = account->bank->loanInterest;

    return true;
}

bool PayLoan(Account *account)
{
    if (!account->active || !account->loan.active)
    {
        return false;
    }

    double amountPayable = account->loan.amount * account->loan.interest;

    if (account->balance < amountPayable)
    {
        return false;
    }

    account->balance -= amountPayable;
    account->bank->money += amountPayable;
    account->loan.active = false;
    account->loan.amount = 0;
    account->loan.interest = 1;

    return true;
}

bool Transfer(double amount, Account *sender, Account *receiver)
{
    if (!sender->active || !receiver->active)
    {
        return false;
    }

    if (sender->balance < amount)
    {
        return false;
    }

    double transferFee = 0;
    if (sender->bank != receiver->bank)
    {
        transferFee = sender->bank->transferFeeRate * amount;
        sender->bank->money += transferFee;
    }

    sender->balance -= transferFee;
    sender->balance -= amount;
    receiver->balance += amount;

    return true;
}

bool CollectLoanPayments(Bank *bank)
{
    for (int i = 0; i < bank->nAcc; i++)
    {
        if (bank->accounts[i]->loan.active && !PayLoan(bank->accounts[i]))
        {
            return false;
        }
    }
    return true;
}

bool CloseAccount(Account *account)
{
    if (account->loan.active && !PayLoan(account))
    {
        return false;
    }

    account->active = false;
    account->balance = 0;
    return true;
}

Bank *ForceDestroyBank(Bank *bank)
{
    // Check if bank exists
    if (!bank)
        return NULL;
    // Just free the memory
    for (int i = 0; i < bank->nAcc; i++)
    {
        free(bank->accounts[i]);
    }
    free(bank->accounts);

    free(bank);
    bank = NULL;
    return NULL;
}

void ShowAccount(Account *account)
{
    printf("Account #%d:\n", account->id);
    if (account->active)
    {
        printf("Balance: %.3f\n", account->balance);
        if (account->loan.active)
        {
            printf("Loaned %.3f with interest %f\n",
                   account->loan.amount, account->loan.interest);
        }
    }
    else
    {
        printf("Inactive account\n");
    }
}

void ShowBank(Bank *bank)
{
    printf("BANK:\n");
    printf("Total money in bank: %.3f\n", bank->money);
    printf("Maximum loan offered: %.3f\n", bank->maxLoan);
    printf("Interest for loans: %f\n", bank->loanInterest);
    printf("Fee for a money transfer: %f\n", bank->transferFeeRate);
    // printf("----------------\n");
    for (int i = 0; i < bank->nAcc; i++)
    {
        ShowAccount(bank->accounts[i]);
        printf("----------------\n");
    }
}
