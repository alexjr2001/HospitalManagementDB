# HospitalManagementDB

## Description
In this project, developed in 2020, we manage a database of a company where we put into practice the concepts of OPP, pointers, polymorphism, abstraction, inheritance, etc. The CRUD of users such as Doctors, Administrators and Patients is available, that is what makes most of the project. Also, you would book appointments if you are a patient, you look for your pending appointments of the day if you are the doctor and finally, you can control all of it if you are an administrator, you will even find medical records.

Moreover, if you want internal management the doctor can communicate with the admi without the patient knowing and vice-versa, in order to change his schedule or request some information. 

## Usage
You can set the limit of people in the main where we create the pointers in main.cpp.

<p align="center">
<img width="354" alt="image" src="https://github.com/alexjr2001/HospitalManagementDB/assets/63054183/8954e5a2-e633-4485-b6db-431ef28a80b0">
</p>

When you execute the code there will be a form that is supposed to be filled out by the first and top-level administrator (Fig. 1), where you type your personal information and your password. If everything goes as planned in the program, you will see a menu where you can exit, create a patient or log in to manage doctors o create them (Fig. 2).

<p align="center">
<br>
<img width="426" alt="image" src="https://github.com/alexjr2001/HospitalManagementDB/assets/63054183/bfea16a7-b9f4-4cbc-a031-7a4ff336500f">
<br>Fig. 1: Here we have the form of the top-level administrator.<br><br>
<img width="326" alt="image" src="https://github.com/alexjr2001/HospitalManagementDB/assets/63054183/d4518144-312a-4156-9f2c-b79569bcf734">
<br>Fig. 2: If you read the instructions, you should be here.
</p>

In the following image, we can see the administrator menu after having logged in (Fig. 3) where you can edit your information (1), see messages of the doctors (2), add a doctor, patient or admi (3); look up information of a patient or a doctor (4) and finally, log out option (5)
<p align="center">
<img width="352" alt="image" src="https://github.com/alexjr2001/HospitalManagementDB/assets/63054183/171393f7-d187-420e-8c57-306a2e161fc0">
<br>Fig. 3 If you hit the right ID and Password.
</p>

## Compilation and execution
After understanding that you can compile it and run it!
```
>> g++ main.cpp Hospital.cpp
>> ./a.exe
```


