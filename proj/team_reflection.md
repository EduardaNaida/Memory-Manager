# Group A11

## Participant list

Name | Email | Active dates
---- | ----- | ------
Eduarda Naida | Eduarda.Naida.1349@student.uu.se | 14/12-20 – 14/12-21
Kimiya Rahimi Ata | Kimiya.Rahimiata.4233@student.uu.se | 14/12-20 – 14/12-21
Lukas Nord | Lukas.Nord.9726@student.uu.se | 14/12-20 – 14/12-21
Max Sahlholm | Max.Sahlholm.6598@student.uu.se | 14/12-20 – 14/12-21
Ludvig Westerholm | Ludvig.Westerholm.7983@student.uu.se | 14/12-20 – 14/12-21
Anton Ohlsson | Anton.Ohlsson.1948@student.uu.se | 14/12-20 – 14/12-21

## Quantification

* Project start date: 17-12-20
* Project end date: 14-01-21

Sprint nr | Start date | End date
---- | ----- | ------
Sprint 1 | 14-12-20 | 18-12-20
Sprint 2 | 21-12-20 | 22-12-20
Sprint 3 | 28-12-20 | 31-12-20
Sprint 4 | 01-01-21 | 08-01-21
Sprint 5 | 11-01-21 | 13-01-21

![Sprint burndown chart](burndown_chart.png?raw=true "Sprint burndown chart")

* Total number of new lines of C code: 220
* Total number of lines of test code: 341 
* Total number of lines of "script code": 73
* Total number of hours worked by the team: 206
* Total number of git commits: 90
* Total number of pull requests: 11
* Total number of GitHub issues: 0 (see Missing tools)

## Process

### Inception

The development process that was chosen for this project was Scrum. This particular process was chosen mainly due to it's applicability to working life. This is because Scrum consists of a dev-team, a Scrum master(Project manager) and a product owner. While this project is missing a few key components for a Scrum-development, lacking for example a customer and a product owner, it's essence is still here. This mindset can be applied to future projects and is therefor a great learning experience. 

To learn about this process, a couple of people from the group took it upon themselves to understand how the development process works and how it should be implemented. They later held a meeting with the group and shared their understanding of it.

A google drive document was created and shared between all the members. This document was to contain all the necessary information needed to understand and implement the process. All the sprints and backlogs were to be shared in the document.

### Implementation

The groups understanding of a Scrum work-process was implemented. Each sprint were decided to be of about a weeks length. Each sprint began with a sprint planning session were the next sprint were decided and the work was divided between the three work pairs. A daily meeting were held where progress was discussed. If a group were finished with a sprint task the others were updated about what other task they began working on. At the end of each sprint a sprint review were held where each pairs progress was discussed in more detail.

#### Planning

During the sprint planning session the group agreed on a reasonable amount of work for the sprint. The key sprint plans of the project were the implementation of allocate and deallocate, cascade_limit, default_deconstructor, changing assignment 2 to be using the memory manager and the usage of a bitmap in default_deconstructor. Running alongside these plans were the writing of the report and continuously extending the tests. The sprint plans were mostly followed. The default_deconstructor ran over time and the implementation of a bitmap were skipped due to lack of time. 

#### Decisions

The decisions were made in group discussions. The key decisions were whether retain should be done in the constructors of the implementation in Assignment 2 or after being called and if the default_deconstructor should scan for pointers or have the user define the object. Retain was to be called outside of the constructors and the default_deconstructor scans for pointers. Since the group was in full agreement on the decisions they were all followed.

#### Process review

The daily meetings makes it easy to keep the whole group updated on the work progress and any problem that arises. The planning sessions gives everyone a clear view of what should be done. The review session keeps everyone updated on what has been done and how it has been done. Since there was no product owner the interpreting of the instructions could sometimes take time because the group had to wait for a meeting with a TA. 

Since the project already was done completely at a distance the Christmas break was not a problem. A small break over Christmas and then over New year was agreed upon and followed. The process that was used worked fine. Each sprint had clear goals and the meetings ensured good cooperation which would be useful in a future project. One thing that could be better was that a clear Scrum master was never used. This made the meetings take a bit longer since most decisions led to a group discussion. Some time could be saved if someone had the final say.

## Use of Tools

The tools that were chosen for this project were Github, Discord, Zoom and Google Drive for communication among the group members, while Valgrind, CUnit and Gdb was used to develop code and Overleaf for drafting the rapport. 

### Github

Github was used to share code between our coding groups in a practical way.  No one in thegroup  felt  confident  with  using  Github  but  since  it  is  a  tool  that  is  commonly  used  in  thework-life, it was a perfect opportunity to become familiar with it.

### Communication

Google Drive, Discord and Zoom was on the other hand platforms that had been used previousto this project and were the obvious choices for communication.  Discord was the tool that wasused for all of the group meetings while Google Drive was used to share all of our documents including all of our scrum planning and our backlog.  Using Google Drive allowed everyone inthe group to easily being able to access and edit the document at any time.  Zoom was onlyused when meetings where held with our coach Fredrik.

### Developing code

Valgrind was the tool chosen for discovering potential memory leaks in our program, and CUnitwas used to create standardised tests for the program, and if those tests were to fail, Gdb couldbe used to help us understand why it failed.  These are tools that were a big part of the firstsprint  of  the  course  and  they  have  been  used  almost  since  day  one.   It  therefor  made  senseto bring them back for this project as the shared experience of those tools were considerable.Choosing tools that the team knew how to use beforehand felt like an huge advantage.  Thismeant that spending time getting familiar with the usage of tool could be avoided.

### Reflection of the chosen tools

The team is content with the tools that were chose since no problems were encountered duringthe usage of them.  However, it would have been more comfortable and useful if Zoom wouldhave replaced with Discord.  Since all of the communication between the team members tookplace on Discord, the coach did not take part of the daily scrum since all communication withthe coach was via Zoom.  The transition between Discord and Zoom felt unnecessary, and couldhave been avoided.

### Missing tools

Gcov is a tool that is used for measuring code executed in a program.  This is a tool we didn’tthink about using until the very end of the project.  At this time there was not a lot of time tomake use of the information provided by the tool since we were not able to potentially rewrit eour code.  This tool would have been of great use during the development, but we did not useit effectively.

While it is hard to argue that it is in fact a "tool" of some sort, the act of meeting with your team in real life, is very different from chatting in Discord. While it worked well to chat online, it would have been rewarding to have meet ups in real life to discuss the project. Meeting in real life can sometimes make the working hours more effective and also make you more motivated to work together.

The GitHub "Issue" tool was not utilized at all during this project. This is due to the high level of interaction between all group members and coding pairs, making a separate issue tracking service less useful. It would however be convenient to have a list of issues that have been solved throughout the project. All in all, any issues that popped up were resolved in a timely manner without this tool.

Doxygen was used to generate documentation. This is due to a lack of time during the latter parts of the project. All comments, however, are written according to doxygen standards.

## Communication, Cooperation and Coordination

### Benefits of Daily scrum

An enormous perk of using the scrum method is having the daily scrum meeting, where we would share the work that had been done the day before and our thoughts about coming days. Each member is either given a specific task, or informs the group of what work they have planned for the day. The meetings progress without a set agenda, and everybody is given time to speak. This also allowed every member to share their thoughts in general, which could be stuff not directly related to the project. Since this is not the only course that was taken during this period of time, and since not all courses between all members were shared, this allowed for prosperous communication among the team. Communication is after all key in a project. And since we communicated almost every day, it was easy to deal with almost anything, such as schedule conflicts with exams, stress, etc. This allowed us to be flexible to every member's schedule.

### Communicating in the team

After a brief discussion on Zoom, the group agreed on using Discord as the main form of communication. Using a private server, all further meetings were held in this environment - except for irregular specific meetings with the project supervisor, our coach, Fredrik Nysjö, which were held on Zoom.

Communication is done mainly through the daily scrum meetings, and continually within pairs during scheduled work hours. In the event that a group is stuck or needs to ask questions to a specific member of another group, this was handled easily over Discord. There was little to no actual issues with communication, aside from negligible tardiness in joining up for briefings. As long as there was at least one member of each group present, the meetings could continue without delay.

The group discussed how much time would be needed for the project to finish and decided which days would be used as holidays. Other than the days used as holidays, the project continued as before since there was no physical meet ups.
 
### Continuous code reviewing

In order to make sure that no unwanted changes were merged into the main code, meetings were held where every team member collaborated when merging larger parts of the project, such as branches of entirely new functionality, or larger refactoring. Since the group as a whole could be considered quite new to GitHub, a lot of time was spent making sure that the right commands were used, as well as making sure that the branches and changes were structured in a somewhat organized way.

### Lessons learned

A problem that was encountered was delegation in the start of the project. At times work would be assigned to a coding group without enough knowledge about the task. During the daily scrum in the first week of development, a couple was assigned to implement the cascade limit. At the time of that assignment, not enough was known about what the actual function of the cascade limit would do. The result of this was that the coding couple spent the whole working day trying to implement something that was not yet implementable during that time of the development. This taught us a lesson to try to have an overall understanding of every assignment delegated. Rather than just delegating, without knowledge of the task given.

## Work Breakdown Structure

### Pair programming

Pairing was used throughout the project. This is because the group felt that the project was hard to divide into smaller parts suited for individual programming. If individual programming would have been used the group felt that too much time would have been spent on keeping each other on individual progress. Pair programming was also viewed as more effective since the group members are not that proficient in programming and being able to exchange ideas right away is very useful. There was great communications between all members in the group during each meeting. Work was not assigned to a member or a coding couple without a discussion beforehand. This was done to ensure that every member felt comfortable with the work assigned to them for the day, and that no member felt overwhelmed. 

### Workload balances

The work load was balanced by ensuring that each pair has done some report writing and some programming on most of the parts of the program. Meaning that between sprints each pair switched between writing the report and programming on each part of the problem, for example there is two pairs that have worked on the tests. Arguably not the most efficient way to work but the group felt that some focus could be given to learning by having each pair work on most of the parts of the project.

Furthermore, in the case that a pair was stuck and needed a third (or fourth) opinion on topics as for example how to structure code, solve an issue, find a memory leak, or something of that nature, it was often easy to reach the other pairs in the project Discord channel. Since the code was often written by another group, this felt like a convenient solution - and turned out to work quite well. If the pair in question could not reach anyone, the issue was brought up in the following briefing and time was scheduled for the concerned groups to collaborate before starting their new assignments of the day.

### Assigning work

The tasks were divided according to workload and need, with pairs often doing either coding (which could entail coding in the exact same part of the program, or spread out in different parts) or code-adjacent project work (which mostly meant either writing/reading the report, writing project documentation or assignment details). Since pair members could sometimes be working very separate, it wasn't that big of a deal if the member of a pair was consulted to help out other pairs, a typical example being helping refactoring of code they wrote (or simply explaining it in detail, if documentation was lacking). 
 
We found it challenging to estimate how much time any given task would take without having worked with it first. It was when any given pair first jumped into it that an estimate could be given. This estimate would then be given on the upcoming daily scrum.

## Quality Assurance

### Tests

The tests written were oftentimes initially meant to test very specific functionality that was written by the same pair writing the tests. This is only natural, given that pairs often rotated to different parts of the project, and therefore making sure that the code that a specific pair had written worked was of great importance and prioritized so that the code could be pushed and used by other pairs without having to worry about functionality. When implementing the new memory management interface into assignment 1 and 2, large parts of the already written tests were reused, only changing memory allocation functions. 

Fortunately, the project was very linear in terms of addition of functionality, and working with the assumption that previous groups had pushed tested (and working) code gave way for fast and agile progression of the project. In the instance that pushed code had missed some sort of edge case, the solution was usually for the "coding-pair" to go over the code at surface-level, and if the issue was not immediately detected, to contact the pair that wrote it initially. 

### Project specification

The project specification was mostly very clear, however, there were cases where the group struggled in understanding specific parts of an instruction or requirement. One example of this was the limit to memory overhead of each allocated object, which was supposed to not be more than two times the size of the allocation pointer. Issues like this one was brought up internally, and if no conclusion was reached in the groups own discussions, the group simply passed the question onto our designated project supervisor. For example, the requirement of memory efficiency in the new functions compared to calloc and malloc. This was not explained very well in the specifications, and thus the group had to ask for further explanation by the supervisor. Another example would be the statement which makes it sound like we are supposed to call the destructor for each non-NULL element in an allocated array. We discussed this and decided that destructing the elements individually would be up to the user, since we did not understand how this would work for most datatypes.

### Pull requests

Pull requests were often managed collectively, with each pair attending a small meeting about the merges. This meant that all team members collectively code reviewed all the written code continuously during the entire project. This worked quite well as the size of the project and team allowed for it. Pull requests were either made during this meeting, or made prior to them and briefly discussed before being either accepted or disregarded. Due to the happenstance of new features being built upon code in a branch that had not yet been pulled into the main branch, some pull requests were ignored since they were basically overlapping later ones. 

Because of this way of using pull requests, the names and descriptions of pull requests were not that crucial in order to understand what was being merged - the group was in a meeting during the merge, and the pair responsible for any code to be merged could simply explain it verbally. However, some pull requests referenced "tests" without specifying which tests. This is understandable, since they were earlier pull requests, at which point there was only a single test file. Furthermore, many pull requests lacked proper (or any) description. The most understandable pull request is one of the later ones, which added functionality, reorganized folder structure and renamed functions. As this was a rather large change, it was properly named and had a description that also used a permalink to some of the changed code.

Since the project was fairly small in scale, and the group kept in touch almost every day, using pull requests was more of a formality than something that felt necessary. It was, however, very convenient to stage changes to the code into these pull requests. It made for a clear picture of how the code was changed, and what branch implemented what.

## Reflection

### Process satisfaction

There were no major setbacks, and each and every member contributed to the project in a meaningful way. The daily briefing meetings were of great benefit and boosted the groups morale, as well as kept every member informed throughout the entire project. Even if a pair was stuck, the issue/issues were handled in a timely manner. This agile and flexible way of assigning work made it possible for each member to work in areas where they excel. Working in coding couples was a very comfortable way of working, since couples were assigned an area to work on for each daily scrum. However there is room for improvement with regards to our chosen way of working. The coding couples were randomly put together during the groups first meeting. The coding couples remained static during the entire project. It may have been wise to alter the assembly of the given coding couples in order to not get reliant on anyone and making sure everyone can co-operate with any given group member. This could have been achieved by rotating after every sprint review. The groups satisfaction with the process has been measured at 6 out of 7.

### Product satisfaction

With regards the satisfaction to the delivered product, all wanted features has yet to be implemented. Which obviously lowers the value of the shared satisfaction of the delivered product. However, the product that was produced still meets the agreed upon function requirements. Those features are also well tested and working satisfactorily. While the product may be improved upon, with regards to memory efficiency among other things, the overall product works as intended. The groups satisfaction with the end product is 5 out 7.

### Quality assurance

Quality Assurance did not present any large issues. Since each pair was responsible for testing their own functions, any code pushed and used was well tested before implementation. Since the implementation was somewhat linear, any code built later in the project was usually built upon already tested code. As for implementation of the new functions, there were already quite rigorous test files in place for assignment 1 and 2, which gave way for quick writing of rewriting - mostly simply replacing alloc and calloc with allocate and allocate\_array, and using release instead of free. Since it is mean to explicitly replace those functions, the already existing memory tests were reused this way. The groups satisfaction with the quality assurance is 5 out 7.

### Biggest win

The biggest win of the project is finishing the required functions and having them pass a multitude of tests, including actual implementation in the form of usage as a memory handling interface in a different program. All of the functions specified by the project documents are in place and work as expected.

### Biggest fail

In terms of shortcomings, there is definitely room for improvements when it comes to optimization. As the team didn't foresee all the bugs popping up at a fairly late stage of the project, the amount of time spent on optimization was significantly reduced, and replaced by time spent on making sure the basic functionality of the program was stable. Fortunately, there were no massively unoptimized functions in place during this time, as many design choices made early on made for efficient code. Some solutions could be more elegant, such as the renaming of all rewritten hash table and linked list functions - which the group thought wouldn't be necessary but ultimately could not find a solution to avoid. Either way, the code functions properly.



