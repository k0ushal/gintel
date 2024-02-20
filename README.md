This is a POC to the concept of building intellisense over multiple C++ code repositories.
The goal is to make finding reusable code easier within the organization. 

While I was working with a company, one day I realized that some of the code I'm writing to solve some problem right now has probably been already written by someone else in their own team. They took the time to analyze and solve the problem, write unit-tests and fix any bugs found during testing. They probably spent 2 weeks making it ready for deployment.
If I had knowledge about that, I could reuse their code (perhaps with little changes) and save myself 2 weeks of reinventing the whole wheel. But unfortunately this isn't possible as we don't interact with other teams at such granular level on a day to day basis. So the knowledge of the existence of such readily available solutions is missing.
There are 10s if not 100s of teams within the company. If all of them could reuse code from each other, the company could deliver products much faster and save on Engineering costs.

So I decided to build an index over multiple code repositories. I'm using CLANG to parse C++ code and use that information to build a global index over all repositories.
Using this index, I can provide typeahead suggestions for user-specified search terms. The index contains information about classes, methods, functions, structures, etc. 

My next step is to build a VS Code extension with a search bar where users can start typing relevant keywords and they get type-ahead suggestions and a full list of matches for their search queries.
Users also get detailed information about the source code where their desired classes or functions can be found.
