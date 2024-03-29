#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class Ice: public AMateria
{
    private:

    public:
        Ice();
        Ice(const Ice &cls);
        ~Ice();

        Ice &operator=(const Ice &cls);

        AMateria *clone() const;
        void use(ICharacter &target);
};

#endif