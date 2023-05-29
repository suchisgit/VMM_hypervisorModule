#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unistd.h>

using namespace std;

class VirtualMachine{
	public:
		string vm_binary;
		int registers[32];
		int hi;
		int low;
		int currInstruction;
		vector<string> instructions;

	VirtualMachine(string path,string snapshot){
		vm_binary=path;
		// memset(registers,0,sizeof(registers));
		if(snapshot.length()==0){
			// cout << "inside no snapshot part" << endl;
			for(int i=0;i<32;i++){
				registers[i]=0;
			}
		}else{
			// restoring the snapshot Values
			// cout << "inside restoring snapshot part" << endl;
			ifstream file(snapshot+".txt"); // open the file
    	string line;
			int i=0;
			if (file.is_open()) {
        while (getline(file, line) && i<32) {
						registers[i]=stoi(line);
						i++;
        }
        file.close(); // close the file
    		}
			else {
      	cout << "Failed to open file.\n";
    		}
		}
		hi=0;
		low=0;
		currInstruction = 0;
		instructions=getAllInstructions(vm_binary);
	}

	// This method is a common method to check the commaSeperatedValues size based on the instruction type.
	bool checkRightPortionlength(vector<string> commaSeperatedValues,int s,string assemblyCommand){
		// cout << commaSeperatedValues.size() << endl;
		if (commaSeperatedValues.size() != s){
			cerr << "Error: Invalid" + assemblyCommand + "command" << endl;
			return false;
		}
		return true;
	}

	int dollarNum(string s){
		int len=s.length();
		return stoi(s.substr(1,len-1));
	}
	// This method will return a vector of all Instructions.
	vector<string> getAllInstructions(string filename){
		vector<string> instructions;
		ifstream file(filename);
		if (!file.is_open()) {
				cerr << "Error: Could not open file " << filename << endl;
				// return 1;
		}
		string line;
		while (getline(file, line)) {
			instructions.push_back(line);
		}
		return instructions;
	}

	//This method is running the MIPS instruction for a singe instruction.
	int runMIPSinstructions(string instruction){
		if(instruction==""){ // to handle blank lines at the end.
			return 0;
		}
		vector<string> lineParts=splitString(instruction,' ');
		string instruction_l=lineParts[0];
		string instruction_r=lineParts[1];
	  if(instruction_l=="li"){
	    //need to split "$1,6"
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,2,"li")){
	      return 1;
	    }
	    //logic
	    int regIndex=dollarNum(commaSeperatedValues[0]);
	    registers[regIndex]=stoi(commaSeperatedValues[1]);
	  }
	  else if (instruction_l=="add") {
	    // add $4,$1,$2 #$4=$1+$2=30
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"add")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]+registers[index3];
	  }
	  else if (instruction_l=="sub"){
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"sub")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]-registers[index3];
	  }
	  else if (instruction_l=="addi"){
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"addi")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int val3=stoi(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]+val3;
	  }
	  else if (instruction_l=="addu") {
	    // how to convert the original registers to unsigned ?
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"addu")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    unsigned int val2=registers[index2];
	    unsigned int val3=registers[index3];
	    registers[index1]=val2+val3;
	  }
	  else if (instruction_l=="addiu"){
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"addiu")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    unsigned int val2=registers[index2];
	    unsigned int val3=stoi(commaSeperatedValues[2]);
	    registers[index1]=val2+val3;
	  }
	  else if (instruction_l=="subu") {
	    // how to convert the original registers to unsigned ?
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"subu")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    unsigned int val2=registers[index2];
	    unsigned int val3=registers[index3];
	    registers[index1]=val2-val3;
	  }
	  else if (instruction_l=="mul") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"mul")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]*registers[index3];
	  }
	  else if (instruction_l=="mult") {
	    // cout << "mult" << '\n';
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,2,"mult")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    long int val1=registers[index1];
	    long int val2=registers[index2];
	    long int product = val1*val2;
	    unsigned int ones32=pow(2, 33)-1;
	    hi = product >> 32;
	    low = product & ones32;
	  }
	  else if (instruction_l=="div") {
	    // cout << "here" << endl;
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,2,"div")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    hi = registers[index1]%registers[index2];
	    low = registers[index1]/registers[index2];
	  }
	  //Logical operations.
	  else if (instruction_l=="and") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"and")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]&registers[index3];
	  }

	  else if (instruction_l=="or") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"or")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int val3;
	    if (commaSeperatedValues[2][0]=='$'){ //or with third parameter as register
	      // std::cout << "inside if" << '\n';
	      int index3=dollarNum(commaSeperatedValues[2]);
	      val3=registers[index3];
	    }else{//or with third parameter as value
	      // std::cout << "inside else" << '\n';
	      val3=stoi(commaSeperatedValues[2]);
	    }
	    // cout << val3 << endl;
	    registers[index1]=registers[index2]|val3;
	  }
	  else if (instruction_l=="andi") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"and")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int val3=stoi(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]&val3;
	  }
	  else if (instruction_l=="sll") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"sll")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int val3=stoi(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]<<val3;
	  }
	  else if (instruction_l=="srl") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"srl")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int val3=stoi(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]>>val3;
	  }
	  else if (instruction_l=="xor") {
	    vector<string> commaSeperatedValues = splitString(instruction_r,',');
	    if (!checkRightPortionlength(commaSeperatedValues,3,"xor")){
	      return 1;
	    }
	    //logic
	    int index1=dollarNum(commaSeperatedValues[0]);
	    int index2=dollarNum(commaSeperatedValues[1]);
	    int index3=dollarNum(commaSeperatedValues[2]);
	    registers[index1]=registers[index2]^registers[index3];
	  }
	  else if (instruction_l=="DUMP_PROCESSOR_STATE") {
			//pretty printing the registers.
	    for(int i=0;i<32;i++){
	      cout << "R" << i << "=" << registers[i] << endl;
	    }
	  }
		else if (instruction_l=="SNAPSHOT"){
			string snapName = instruction_r + ".txt";
			ofstream snapShotFile(snapName);
			if(snapShotFile.is_open()){
				for(int i=0;i<32;i++){
						snapShotFile << registers[i] << endl ;
				}
				snapShotFile.close();
				cout << "successfully created snapshot" << snapName << endl;
			}else{
				cout << "Error: Could not create file." << std::endl;
			}
		}
		currInstruction++;
		return 0;
	}

	vector<string> splitString(string str, char delimiter) {
	    vector<string> tokens;
	    string token;
	    istringstream tokenStream(str);
	    while (getline(tokenStream, token, delimiter)) {
	        tokens.push_back(token);
	    }
	    return tokens;
	}
};

class VirtualMachineMonitor  : public VirtualMachine {
	public:
		int vm_exec_slice_in_instructions1;
		int vm_exec_slice_in_instructions2;
		VirtualMachine VM1;
		VirtualMachine VM2;

	VirtualMachineMonitor(int slice1,int slice2,VirtualMachine vm1,VirtualMachine vm2): VirtualMachine(vm1),VM1(vm1),VM2(vm2){
		vm_exec_slice_in_instructions1=slice1;
		vm_exec_slice_in_instructions2=slice2;
	}

	// This method is used to create the order of the execution based on the slices of each VM.
	vector<int> executionOrderVector(){
		vector<int> order;
		int size1;
		int size2;
		int noOfIns1=numberOfInstructions(VM1);
		int noOfIns2=numberOfInstructions(VM2);
		int totalIns=noOfIns1+noOfIns2;
		int totalInsdup=totalIns;
		while(totalIns!=0){
			if( noOfIns1!=0 ){
				if (noOfIns1>vm_exec_slice_in_instructions1){
					size1=vm_exec_slice_in_instructions1;
				}else{
					size1=noOfIns1;
				}
				noOfIns1-=size1;
				totalIns-=size1;
				for(int i=0;i<size1;i++){ order.push_back(1); }
			}
			if( noOfIns2!=0 ){
				if (noOfIns2>vm_exec_slice_in_instructions2){
					size2=vm_exec_slice_in_instructions2;
				}else{
					size2=noOfIns2;
				}
				noOfIns2-=size2;
				totalIns-=size2;
				for(int i=0;i<size2;i++){ order.push_back(2); }
			}
		}
		return order;
	}

	int numberOfInstructions(VirtualMachine VM){
		return VM.instructions.size();
	}

	// This method is utilized to trigger execution of each instruction based on the vm_exec_slice_in_instructions of the VM
	void triggerExecutionWithContextSwitch(vector<int> order){
		for ( int i=0;i<order.size();i++ ){
			if ( order[i] == 1){
				// cout << "From VM-1" << endl;
				if (VM1.instructions[VM1.currInstruction]=="DUMP_PROCESSOR_STATE"){
					cout << "-----" << endl;
					cout << "VM-1:" << endl;
				}
				VM1.runMIPSinstructions(VM1.instructions[VM1.currInstruction]);
				// cout << "ran instruction-1" << endl;
			}else{
				// cout << "From VM-2" << endl;
				if (VM2.instructions[VM2.currInstruction]=="DUMP_PROCESSOR_STATE"){
					cout << "-----" << endl;
					cout << "VM-2:" << endl;
				}
				VM2.runMIPSinstructions(VM2.instructions[VM2.currInstruction]);
				// cout << "ran instruction-2" << endl;
			}
		}
	}

};

int main(int argc, char* argv[]) {
		int opt;
		string snapshot_file1,snapshot_file2,assembly_file1,assembly_file2;
		while ((opt = getopt(argc, argv, "v:s:")) != -1) {
		    switch (opt) {
		        case 'v':
		            if (assembly_file1.empty()) {
		                assembly_file1 = optarg;
		            } else if (assembly_file2.empty()) {
		                assembly_file2 = optarg;
		            }
		            break;
		        case 's':
		            if (snapshot_file1.empty()) {
		                snapshot_file1 = optarg;
		            } else if (snapshot_file2.empty()) {
		                snapshot_file2 = optarg;
		            }
		            break;
		        default:
		            break;
		    }
		}
		// cout << "fileNames" << endl;
		// cout << assembly_file1 << "," << assembly_file2 << "," << snapshot_file1 << "," << snapshot_file2 << "." << endl ;
		string pwd="";
		//file1 operations
		// cout << pwd+assembly_file1 << endl ;
		ifstream input_file1(pwd+assembly_file1);
		int slice1;
    string filename1;
		if (input_file1.is_open()) {
				// cout << "inside line 422" << endl ;
        string line;
        while (getline(input_file1, line)) {
            if (line.find("vm_exec_slice_in_instructions=") != string::npos) {
                slice1 = stoi(line.substr(line.find("=") + 1));
            } else if (line.find("vm_binary=") != string::npos) {
                filename1 = line.substr(line.find("=") + 1);
            }
        }
        input_file1.close();
		}
		//file2 operations
		ifstream input_file2(pwd+assembly_file2);
		int slice2;
    string filename2;
		if (input_file2.is_open()) {
        string line;
        while (getline(input_file2, line)) {
            if (line.find("vm_exec_slice_in_instructions=") != string::npos) {
                slice2 = stoi(line.substr(line.find("=") + 1));
            } else if (line.find("vm_binary=") != string::npos) {
                filename2 = line.substr(line.find("=") + 1);
            }
        }
        input_file2.close();
		}
		filename1 = pwd+filename1;
		filename2 = pwd+filename2;
		VirtualMachineMonitor VMM(slice1,slice2,VirtualMachine(filename1,snapshot_file1),VirtualMachine(filename2,snapshot_file2));
		VMM.triggerExecutionWithContextSwitch(VMM.executionOrderVector());
    return 0;
}
