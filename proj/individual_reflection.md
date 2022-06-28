## Anton Ohlsson individual reflection

I work ok in a team. I avoid taking front roles and prefer doing something focused as opposed to big picture stuff. I rarely have problem getting along with group mates enough so that it is not a hindrance for working together.

My strengths in a project is that if I am assigned something i try to do it at the best of my abilities. 

Some of my weaknesses is that my motivation is usually dependent on the group, if they work hard I do too but if they do not I do not either. I am not that good at arguing for my opinion on something, I usually give in easily and mutter internally instead. When I am stressed I become irritable and prefer working alone which is not optimal in a group. 

The foremost thing I need to get better at is arguing for my opinion instead of giving it up and telling myself that I do not care.

I do not have strong opinion on working alone or in a group, both is fine with me. A group is better for exchanging ideas. Working alone is better since I get to work at my own pace. 

During the course I learnt more about programming at its core. During the project I learnt more about bigger picture programming, how to work in a group, the usage of github, the Scrum process. All in all I would say I learnt more during the course. But the knowledge from the project is going to be very useful in the work life.

I am not that good at estimating how long something will take. I would not say that I have a given process, I try to compare the assignment to previous work and ensure  that I double the number I initially thought, especially if it is something I am not completly familiar with.

My time logging was lacking towards the end.

My biggest fail was having deallocate bare in the tests which gave some interesting bugs when cascade_limit was implemented. 
My biggest win was that I realized in the default_destructor that to be able to dereference a void pointer I could first cast it as a double pointer and then dereference it.



## Ludvig Westerholm individual reflection

I find myself to be quite flexible while working as a team. I feel that I am rather comfortable in most kind of roles. I do feel however that I tend to let other people take the leader position, something which I am really fine with. I think I am a pretty good sort of 2nd in command, this is because I am often not afraid to speak my mind.
In this project I however chose to work as part of the gang, which was quite nice. You just take your orders and do them.


I in general I enjoy working in a group or as a pair. But I don't always find it necessary. It really depends on what the actual work is gonna be in the project. If I know what needs to be done and I know how to implement it, then working as a group can at times just feel uncessary. And at times deviate from the work.


I feel like I learned very different stuff from sprint 1 and sprint 2 compared to the project. I learned more about coding during the sprints, while the project taught me more about working as a team and github. I've since long ago realized that I learn something best by doing something over and over again. I felt that I learned the most during assignment 2, which at the end was not just trying to make a line of code compile, but that I could use what I learned from assignment 1 in a great capacity.


It was going great filling the time log in the start, but towards january, the logging staggered. I've learned that I should put it down as I go on during the day and fill the log by the end of the day at the latest or else I'll forget what happened. Memory like a goldfish.


My biggest fail was when I was rewriting some of the user interface tests to work with refmem. I had to rewrite the strdup function to work with allocate in order to be able to call release on it when. And the function worked, but when I put it as an argument in the ask question string function, I didn't just pass the function, I had forgotten to remove the added parameter in the function when I copy pasted it into the ask question string function, which resulted in quite the specatuclar error message.

My biggest win was when all of the business_logic and user_interface tests worked as intended with refmem.


## Max Sahlholm individual reflection

I think the way I function in a team vastly differs from which team I am in, and I feel like I can assume the position which is needed. A weakness would be that I rarely feel like going beyond the minimum to complete it. What motivates me is if the task at hand feels fulfilling and fun, its obviously harder to find the motivation if its something that doesn't feel fun. Real-life happening outside of the work at hand also affect me a lot, but that isn't really related and more of a general personality trait. 

I'd say I'm not very good at estimating how long a task would take, I usually greatly underestimate the time needed, and I mostly go be "feeling" when considering how long something will take.

In this team the role I "assumed" was pretty laid back and mostly listened on what needed to get done, and tried my best at getting it done, ie. not any type of leadership role. I think this is the role I prefer because it feels less stressful and I can easier focus on the task at hand. 

I usually prefer working alone, but its also very nice being able to split the workload between other people as to not feel as overwhelmed as can happen when you are working on something by your self. Also having people to discuss ideas and issues with is very helpful. 

I learned quite a bit by the programming part here, definitely moreso than the other parts of the course, which is weird because this is technically "smaller". I am however not a fan of, and don't think I learn much at all by having to spend time on doing work around the programming though, ie. writing reports etc. I can see how this has its place here though.

Logging the time spent working hasn't been super easy, I work quite sporadically and easily forget to enter the time spent, which means I at a later date have to try to estimate how much time I spent. Otherwise its been fine.

The biggest problem we encountered was a especially nasty bug that we couldn't figure out for ages where it turned out the test-cases were written wrong, and not our actual code in the library. So that was definitely a fail.
Biggest win is ofcourse that we managed to create the full library, following all specifications as far as we are concerned. We managed to complete everything and we can see that it works in a "real life"-scenario.


## Kimiya Rahimi Ata individual reflection
The role i take in a team varies a bit from the dynamic in the team i am put in. If i get a feeling during a meeting that it is not going effectively, or that the team needs someone to take charge, i have no problem taking on that role. If on the other hand there is another team member that is taking the lead during the meeting, i am just as comfortable with that. For me it is preferable to switch it up sometimes, I want to be able to take any role needed in a group I am placed in. Therefore I do not want to be too comfortable with either being the leader or the follower. 

Working in a group can be very giving to me personally. In some areas of work I can be more effective when i work by myself, but I would still say I prefer working in a team when it comes to bigger projects. Working in a team can be more motivating for me, since i know people are counting on me to have gotten work done at the end of each working day. It is also easier to work through difficulties when you have more people to ask for help. 

The project has taught me a lot, but the knowledge it has given me is quite different from the rest of course. When it comes to learning about programming this project has not been as giving as the rest of the parts of the course, since it was not that much code to be written by 6 people. I have however gained a lot of knowledge about working in a team and developing something in a more realistic working-life matter. I believe this can be just as important as my development as a programmer. 

Logging the time that was spent could have been done better. I have been forgetful and therefore I have not always updated the log in time. This led to the log not always being as accurate as i would hope for it to be. I should also have commented better on exactly what my time was spent on for each day. 

I would not say i am particularly good at estimating how long a task will take, especially not when i am not familiar with the concept that we are working with. I would need some time to understand the concept to try making an estimation. During the project this is something that we struggled with in the beginning. It was to my understanding that the more time we spent on working the better I got at estimating the time needed for a task, since I knew more about it.

The biggest problem I encountered during the development was changing all the strdup in inlupp2. We had to write our own version of it, which gave us a bug that we could not find until a whole day later. Actually finding the bug and making sure inlupp2 passed all of the tests is what I would consider to be my biggest win.  


## Eduarda Naida individual reflection

I work well in a team. I choose to work preferably in a group because I can get help from others if I get stuck on something. We had a group of 6 members so it would be less effective if everyone had worked on the same thing, so it suited me perfectly that we had 3 groups with two members.

I feel that I best learn things when I first try to do it alone and then ask for help from others if I get stuck. So here I could mention my weakness is that I ask for help without thinking first about the solution. However, I learned quite a lot during the project, namely using Github, code reviewing, writing code and documentation. The group had a very good communication so I didn't feel any stress to ask some questions if I got stuck on something. The planning of working hours went well even when I had a math exam after the Christmas break.

My biggest fail was that at the beginning I couldn't get the full picture of the project.

My biggest win was that I realized the reason our pointer math was not working was that when 1 is added to a pointer the memory address changes by the size of the object in the pointer.


## Lukas Nord individual reflection

This project has been a success. I felt like I contributed suffieciently to both the coding- and report-side of the project. The workload felt evenly shared, and working in pairs went well. Since me and Max know each other from previous courses, there was no issue working as a pair on either side of the project. 

Generally, I like working in groups. There are situations where having other people to either talk to about my solutions, have explain their solutions to me, is beneficial to learning coding. I do however prefer to code in peace and quiet if there is some bug that takes longer to try to explain rather than fix yourself.

The position I naturally take in a group is not one of a leader, however I have no issue speaking up to voice my opinion either. I'd rather be someone who keeps the structure of the group intact, and mediate between people, rather than set deadlines or issue commands or assignments to other people.

Compared to the rest of the course, I did not learn as much during this project. It might be because the project scope and ambition was quite small, and during implementation we were working with code that I personally previously wrote. It felt more like looking at my own old code and thinking "Wow, did I really write this?". In order to learn, I think that trying to write your own code in your own pace, with a deadline, is better.

Since this project has a larger scope than just coding, I felt very distracted. There is a LOT of writing expected from students, which honestly feels like a waste of time. This sort of reflection is something that most people have done multiple times before, and doesn't quite fit in a course catered to adults who have already gone through multiple stages of education. If anything, this very document feels like an unnecessary timesink, and I would rather see the actual coding part of the project be more front and center, rather than like a 50/50 or even 40/60 split. Less writing words, more writing code. Please.

Logging my working hours has gone quite well. Sometimes I lag behind a day or two, or even a couple, however since we are working in pairs, there wasn't much of an issue to estimate how much time we spend doing something, or what we were doing that day. In fact, since we had briefing meetings every morning, almost everyone in the group knew what each other was doing. 
