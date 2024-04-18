import { useEffect, useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import Router from './component/Router'
import './App.css'

function App() {
  const [count, setCount] = useState(0)
  const [rutaActual, setRutaActual] = useState("app")
  const [flag, setFlag] = useState("false")

  useEffect(()=>{
    if(window.location.pathname == "/"){
      window.location.href = '/home'
    }
    console.log(window.location.pathname)
    setRutaActual(window.location.pathname)
  },[])

  console.log(flag)

  return (
    <>
      <div> 
        <h1>Rutas</h1>
      </div>
      <div>
        <Router ruta={rutaActual} setFlag={setFlag} flag={flag}></Router>
      </div>
    </>
  )
}

export default App
