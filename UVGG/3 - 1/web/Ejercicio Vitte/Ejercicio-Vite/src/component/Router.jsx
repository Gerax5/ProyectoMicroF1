import {userState} from 'react'
import Default from '../view/default';
import Login from '../view/login';
import User from '../view/User';

function Router({ruta,setFlag, flag}){
    
    switch (ruta) {
        case "/home":
            if(!flag){
                return <User></User>
            }else{
                return <Default></Default>
            }
        case "/login":
            return <Login setFlag={setFlag}></Login>
    }
}

export default Router