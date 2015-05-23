multimod_matching_tree
======================

language C. a multiple-mode-string matching method. super simple and super performance.

`  `  
`/*`  
`data structure:`  
`  [head]`  
`	├── [node0]`  
`	├── [node1]`  
`	├── [node2]`  
`	├── [node3]`  
`	│        ├── [node0]`  
`	│        ├── [node1]`  
`	│        ├── [node2]`  
`	│        ├── [node3]`  
`	│        │        ├── [node0]`  
`	│        │        ├── [node...]`  
`	│        │        └── [node255]`  
`	│        ├── [node...]`  
`	│        ├── [node253]`  
`	│        ├── [node254]`  
`	│        └── [node255]`  
`	├── [node...]`  
`	├── [node254]`  
`	└── [node255]`  
``  
`example:`  
`	patterns is:`  
`		string "123" ==> 0x31 0x32 0x33 ==> 49 50 51`  
`		string "132" ==> 0x31 0x33 0x32 ==> 49 51 50`  
`		string "1234" ==> 0x31 0x32 0x33 0x34 ==> 49 50 51 52`  
``  
`		the build tree like this:`  
`		[head]`  
`		└── [node49]{_is_used = true,_is_boundary=false}`  
`		├── [node50]{_is_used = true,_is_boundary=false}`  
`		│        └── [node51]{_is_used = true,_is_boundary=true}`  
`		│		          └── [node52]{_is_used = true,_is_boundary=true}`  
`		│`  
`		└── [node51]{_is_used = true,_is_boundary=false}`  
`		└── [node50]{_is_used = true,_is_boundary=true}`  
``  
`	when use method "match_tree_matching" matching from text or biniry stream example "12345":`  
`		be greedy: return 4;`  
`		not greedy: return 3;`  
``  
`*/`  
``  
``  


