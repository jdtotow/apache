import json, time, requests  

class TestModule():
    def __init__(self):
        self.url = "http://localhost/datanoesis"
    def createUser(self, user):
        response = requests.post(url=self.url+"/create",data=json.dumps(user))
        return response.text 
    def getUsers(self):
        response = requests.get(url=self.url+"/getusers")
        return response.text 
    def getUser(self, email):
        response = requests.get(url=self.url+"/getuser"+email)
        return response.text 
    def updateUser(self,email):
        pass 
    def deleteUser(self,email):
        response = requests.delete(url=self.url+"/deleteuser"+email)
        return response.text 


def main():
    test = TestModule()
    users = [{'email':'user-1@data.gr','name': 'user-1'},{'email':'user-2@data.gr','name': 'user-2'}]
    for user in users:
        resp = test.createUser(user)
        print(resp)
    all_users = test.getUsers()
    print(all_users)



if __name__== "__main__":
    main()