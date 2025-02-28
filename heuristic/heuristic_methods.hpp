/* 
   an implementation of Bin Packing and Job Scheduling Algorithm */
#ifndef HEURISTICMETHODS_H 
#define HEURISTICMETHODS_H 

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

struct Bin{
    int size;
    int remain_size;
    std::vector<int> data;
    Bin(int s) : size(s), remain_size(s) {}
};
class BinPacking{
    private:
        int n;
        int L=10;
        std::vector<int> data;
        std::vector<struct Bin> result_bins; // list of bin has created when performing calculation
        std::vector<int> result; // result after perform Strategy (item[i] is in bin[result i])
        std::string strat; // latest strategy performed

    public: 
        /* Constructor */
        BinPacking(std::vector<int> data){
            this->data = data;
            this->n = this->data.size();
        }

        void print_result(){
            std::cout << this->strat << std::endl;
            for (const auto &d : data){
                std::cout << d << ",";
            }
            std::cout << "\b" << std::endl;
            for (int i=0; i<this->result.size(); ++i){
                printf("S%d = %d in Bin %d\n", i+1, data[i], result[i]+1);
            }
            for (int i=0; i<this->result_bins.size(); ++i){
                printf("Bin%d : ", i+1);
                for (int j=0; j<result_bins[i].data.size(); ++j){
                    printf("%d(%d),",result_bins[i].data[j]+1, data[result_bins[i].data[j]]);
                }
                printf("\b\n");
            }
            std::cout << "\n\n";
        }

        /* perform First-Fit Strategy */
        std::vector<int> ff(){
            // clear previous data
            this->result = std::vector<int>();
            this->result_bins = std::vector<struct Bin>();

            this->strat = "First Fit";
            // List of the bin
            std::vector<struct Bin> bins;
            // number of newest bin ever created
            int newest_bin=0; 

            for (int i=0; i<n; ++i){
                int placed = 0;
                this->result.push_back(0);

                // Try to place item to existing bin
                for (int j=0; j<bins.size(); ++j){
                    // check if able to place
                    if (data[i] <= bins[j].remain_size){
                        bins[j].data.push_back(i);
                        bins[j].remain_size = bins[j].remain_size - data[i];
                        placed = 1;
                        this->result[i] = j;
                        break;
                    }
                }
                // if can not place into existing bin
                if (!placed){
                    // create new bin and push an item into it
                    // create new bin
                    struct Bin new_bin = {this->L};
                    // put current item to new bin
                    new_bin.data.push_back(i);
                    // decrease remaining size of new bin
                    new_bin.remain_size = new_bin.remain_size - data[i];
                    // put bin to bins list
                    bins.push_back(new_bin);

                    this->result[i] = newest_bin;
                    // increase bin count
                    ++newest_bin;
                }
                
            }

            this->result_bins = bins;
            return this->result;
        }

        /* perform Best-Fit Strategy */
        std::vector<int> bf(){
            // clear previous data
            this->result = std::vector<int>();
            this->result_bins = std::vector<struct Bin>();

            this->strat = "Best Fit";
            std::vector<struct Bin> bins;
            int newest_bin = 0;
            
            for (int i=0; i<n; ++i){
                struct Bin *best_bin;
                int min_space = this->L+1;
                // number of the best bin
                int best_bin_number = -1; 

                this->result.push_back(0);

                // find to best bin
                for (int j=0; j<bins.size(); ++j){
                    int remaining = bins[j].remain_size;
                    if (remaining >= data[i] && remaining - data[i] < min_space){
                        min_space = remaining - data[i];
                        best_bin_number = j;
                    }
                }
                // if best bin is found
                if (best_bin_number != -1){
                    bins[best_bin_number].data.push_back(i);
                    bins[best_bin_number].remain_size -= data[i];
                    result[i] = best_bin_number;
                }
                // if not create new bin
                else{
                    struct Bin new_bin = {this->L};
                    new_bin.data.push_back(i);
                    new_bin.remain_size = new_bin.remain_size - data[i];
                    bins.push_back(new_bin);
                    this->result[i] = newest_bin;
                    ++newest_bin;
                }
            }

            this->result_bins = bins;
            return this->result;
        }

        /* perform First-Fit decresing Strategy */
        std::vector<int> ffd(){
            // clear previous data
            this->result = std::vector<int>();
            this->result_bins = std::vector<struct Bin>();

            auto compare = [] (const int a, const int b) { return a>b; };
            // sort data 
            std::sort(data.begin(), data.end(), compare); 
            // perform first fit 
            ff();
            this->strat = "FFD (First-fit decreasing)";
            return this->result;
        }

};
struct Process{
    int time;
    std::vector<int> task;
    Process(int time) : time(time){}
};
class JobScheduling{
    private:
        std::vector<int> job;
        int m = 4;
        int n;
        std::vector<struct Process> result;

    public:
        JobScheduling(std::vector<int> job){
            this->job = job;
            this->n = job.size();
        }

        void print_result(){
            for(int i=0; i<result.size(); ++i){
                printf("P%d(%d) : ", i+1, result[i].time);
                for (int j=0; j<result[i].task.size(); ++j){
                    printf("t%d(%d),", result[i].task[j]+1, job[result[i].task[j]]);
                }
                printf("\b\n");
            }

            std::cout << "\n\n";
        }

        std::vector<struct Process> solve(){
            // sort job
            auto compare = [](const int a, const int b){return a>b;};
            std::sort(job.begin(), job.end(), compare);

            // list of process
            std::vector<struct Process> p(m, {0});
            for (int i=0; i<n; ++i){
                // find index of process that have most free time 
                int min_m = find_min(p);
                p[min_m].time += job[i];
                p[min_m].task.push_back(i);
            }
            this->result = p;
            return this->result;
        }

    private:
        int find_min(std::vector<struct Process> &p){
            int min = 0;
            for (int i=1; i<p.size(); ++i){
                if (p[i].time < p[min].time){
                    min = i;
                }
            }
            return min;
        }
};

#endif
