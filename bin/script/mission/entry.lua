--require


test = {}

test.onLogin = function(tID, uID)

	print("onLogin(" .. tID .. ", " .. uID .. ")")
end

trigger.watching(0, test.onLogin)