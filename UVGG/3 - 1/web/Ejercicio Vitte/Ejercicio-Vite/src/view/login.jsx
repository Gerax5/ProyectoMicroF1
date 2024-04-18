import './login.css'
import { useEffect, useState } from 'react'

function Login({setFlag}){
    const [email, setEmail] = useState("")
    const [cont, setCont] = useState("")

    const handleChangeEmail = (event) => {
        setEmail(event.target.value)
    }

    const handleChangeCont = (event) => {
        setCont(event.target.value)
    }

    function vereficar(){
        console.log("email",email)
        console.log("constraseña",cont)
        if(email=="gerax.pineda@gmail.com" & cont=="123"){
            setFlag("true")
        }
    }

    return (
        <>
        <div>
            <p>Ingrese su email: </p><input type="text" id="email" onChange={handleChangeEmail}></input>
        </div>
        <div>
            <p>Ingrese contraseña: </p><input type="text" id='cont' onChange={handleChangeCont}></input>
        </div>
        <div>
            <br></br>
            <button className='btn' onClick={vereficar}>Enviar</button>
        </div>
        </>
        
    )
}



export default Login