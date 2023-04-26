#include <iostream>
#include <string>
#include <vector>

namespace{
    struct egyenlet{
        std::string balOldal;
        std::string jobbOldal;
        char muveleti_jel;
    };

    //precedence
    egyenlet egyenletKeres(std::string kifejezes){
        egyenlet eredmeny;
        //eredmeny.muveleti_jel = kifejezes.at(jelIndex);
        //eredmeny.balOldal = kifejezes.substr(0,jelIndex);
        //eredmeny.jobbOldal = kifejezes.substr(jelIndex+1);
        //TODO find next operator

        return eredmeny;
    }

    float egyenletMegold(egyenlet e){
        float left = std::stof(e.balOldal);
        float right = std::stof(e.jobbOldal);

        switch (e.muveleti_jel)
        {
        case '+':
            return left + right;
        
        default:
            return 0;
        }
    }

        std::string zarojelKeres(std::string& kifejezes){
        size_t lastParenthesisIndex = kifejezes.find_last_of('(');
        size_t unclosed = 1;
        size_t i = lastParenthesisIndex + 1;

        std::string eredmeny;
        while (unclosed != 0 && i < kifejezes.size())
        {
            if(kifejezes.at(i) == '('){
                unclosed++;
            }
            else if(kifejezes.at(i) == ')'){
                unclosed--;
            }

            if(unclosed != 0){
                eredmeny+= kifejezes.at(i);
            }
            i++;
        }
        
        egyenlet egy = egyenletKeres(eredmeny);
        kifejezes.replace(lastParenthesisIndex,i-lastParenthesisIndex,std::to_string(egyenletMegold(egy)));

        return eredmeny;
        
    }


    std::ostream& operator<<(std::ostream& o, egyenlet e){
        o << "Bal oldal:\t" << e.balOldal << std::endl << "Muvelet:\t" << e.muveleti_jel << std::endl  << "Jobb oldal:\t" << e.jobbOldal << std::endl;


        return o;
    }

    void szamolgat(std::string kifejezes){
    //először a zárójeles kifejezéseket kell kiszámolni

    while (kifejezes.find('(') != std::string::npos)
    {
        std::string zarojeles = ::zarojelKeres(kifejezes);
        //std::cout << "Zarojeles: " << zarojeles << std::endl << "Maradt: " << kifejezes << std::endl;
        //std::cout << egyenletKeres(zarojeles,zarojeles.find('+'));
        
    }

    

    //std::cout << "Eredmeny: " << egyenletKeres(kifejezes,kifejezes.find('+'));
    
}

}



namespace{
    std::vector<std::string> felbont(std::string text){
        std::vector<std::string> res;
        for (size_t i = 0; i < text.size(); i++)
        {
            //TODO split text into numbers and operators
        }


        return res;
        
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& o, std::vector<T> v){
        for(T e: v){
            o << e << "\n";
        }

        return o;
    }
}


int main(){
    std::string input = "-10 + (1 + 2)";

    std::cout << felbont(input);



    return 0;
}