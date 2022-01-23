/* This program is one kind of solution of John Bentley's problems in his famous book:
   "The Programming Pearls" chap. 2 ex. 1.
    The problem is to find the missing numbers in 4bl numbers from 0 to UINT_MAX(4294967295)
    For solution I used the binary search paradigm: every time I check if the count of numbers
    which are less or greater then the number_in_use, so I don't care about where the number is,
    the index is not important I mean, the only thing I care about, is the count of numbers,
    after defining the numbers which are less or greater they are tranported to another files,
    after that I choose which file cas more differences and make that file the main file,
    the recursion than starts from considering only that file, olready divided by 2, clears the 
    helping files and do the same thing until I have 1 difference, then it's easy, I count the 
    sum that should be and the sum that exists in the reamining file, substracting I find the 
    missing number!!!
    One more thing: as the numbers are so great and the randonising must be unique, so I
    wrote the code for SIZE_TASK(4bl) and SIZE_CORE(all numbers) for little nunbers, as
    I care about my laptop, it's all for you to generate all the numbers.
    p.s. comments will help to to show the steps of the operations*/

#include <iostream>
#include <fstream>
#include <vector>

const unsigned int SIZE_TASK {1000000u}; //change this if you want (4.000.000)
const unsigned int SIZE_CORE {1000009u}; //and also this (UINT_MAX), #include <climits>

int find(std::string path, std::string path1, std::string path2, unsigned int number_in_use, unsigned int first, unsigned int last) {
    //std::cout<<"number in use: "<<number_in_use<<std::endl;
    std::ifstream main_fin;
    main_fin.open(path);
    if (!main_fin.is_open()) {
        throw ("Can't open the txt doc.\n");
        exit(EXIT_FAILURE);
    }

    std::ofstream fout1;
    fout1.open(path1);
    if (!fout1.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }

    std::ofstream fout2;
    fout2.open(path2);
    if (!fout2.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }

    //for deleting all numbers in both files
    fout1.close();
    fout2.close();

    unsigned int number{0u};    
    unsigned int less_count{0u};
    unsigned int greater_count{0u};
    unsigned int all_count{0u};
    unsigned int less_count_should_be = number_in_use - first;
    unsigned int greater_count_should_be = last - number_in_use;
    unsigned int diff_of_less{0u};
    unsigned int diff_of_greater{0u};
    
    unsigned int sum_of_less{0u};
    unsigned int sum_of_great{0u};
    unsigned int sum_should_be_less{0u};
    unsigned int sum_should_be_great{0u};

    for (unsigned int i = number_in_use + 1; i <= last; i++) {
        sum_should_be_great += i;
    }

    for (unsigned int i = first; i < number_in_use; i++) {
        sum_should_be_less += i;
    }
    
    // filling all numbers less then number_in_use
    fout1.open(path1);
    fout2.open(path2);
    if (!fout2.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    if (!fout1.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    main_fin.clear();
    main_fin.seekg(0);
    while (main_fin >> number) {
        if (number < number_in_use) {
            less_count++;
            fout1 << number << "\n";
            sum_of_less += number;
        } else {
            greater_count++;
            fout2 << number << "\n";
            sum_of_great += number;
        }
    }
    fout1.close();
    fout2.close();

    // std::cout<<"sum_of_less: "<<sum_of_less<<std::endl;
    // std::cout<<"sum_of_great: "<<sum_of_great<<std::endl;
    // std::cout<<"count less in task: "<<less_count<<std::endl;
    // std::cout<<"count less should be: "<<less_count_should_be<<std::endl;
    // std::cout<<"count greater in task: "<<greater_count<<std::endl;
    // std::cout<<"count greater should be: "<<greater_count_should_be<<std::endl;

    diff_of_less = less_count_should_be - less_count;
    diff_of_greater = greater_count_should_be - greater_count;

    // stop point, if there is only one number that does not exists in remaining file
    if (diff_of_less == 1) {
        return sum_should_be_less - sum_of_less;
    } else if (diff_of_greater == 1) {
        return sum_should_be_great - sum_of_great;
    }

    // if diff_of_less is less then pass the file with less of numbers
    if (diff_of_less <= diff_of_greater) {
        std::ofstream main_fout(path);
        if (!main_fout.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        main_fout.close();
        main_fout.open(path);
        if (!main_fout.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        std::ifstream fin2(path2);
        if (!fin2.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        while (fin2 >> number) {
            main_fout << number << std::endl;
        }
        first = number_in_use + 1u;        
        number_in_use = first + (last - first) / 2u;
        return find(path, path1, path2, number_in_use, first, last);
    } else { // do the opposite
        std::ofstream main_fout(path);
        if (!main_fout.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        main_fout.close();
        main_fout.open(path);
        if (!main_fout.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        std::ifstream fin1(path1);
        if (!fin1.is_open()) {
            throw ("Can't open the file\n");
            exit(EXIT_FAILURE);
        }
        while (fin1 >> number) {
            main_fout << number << std::endl;
        }
        last = number_in_use - 1u;
        number_in_use = first + (last - first) / 2u;
        return find(path, path1, path2, number_in_use, first, last);
    }
}

int main()
{
    std::string path_task = "numbers.txt";
    std::ofstream task_out;
    task_out.open(path_task);
    if (!task_out.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    // vector bool is used for unique randomising
    std::vector<bool> vec_task(SIZE_CORE);
    for (unsigned int i = 0; i < SIZE_TASK; i++)
    {
        unsigned int num = rand() % SIZE_CORE;
        if (vec_task[num] == false) {
            vec_task[num] = true;
            task_out<<num<<std::endl;
        } else {
            --i;
            continue;
        }
    }
    task_out.close();

    std::ofstream fout1;
    std::string path1 = "check1.txt";
    fout1.open(path1);
    if (!fout1.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    fout1.close();
    std::ofstream fout2;
    std::string path2 = "check2.txt";
    fout2.open(path2);
    if (!fout2.is_open()) {
        throw ("Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    fout2.close();

    unsigned int number_in_use = SIZE_CORE / 2u;
    unsigned int first = 0u;
    unsigned int last = SIZE_CORE;
    std::cout<<"The missing number is : "<<find(path_task, path1, path2, number_in_use, first, last)<<std::endl;
}