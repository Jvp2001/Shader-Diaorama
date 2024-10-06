<h1>Diorama</h1>

Developed with Unreal Engine 5.3.1

<h2>
User Interaction
</h2>
Other User interaction that I forgot to mention in my video is that you can toggle the dynamic time of day system by pressing the <b>P</b> key on your keyboard.

***

<h2>
Project Structure and Code Efficiency.
</h2>

All of my code was made in blueprint except the Properties panel logic was written in C++. However, the UI was designed
in the UMG WYSIWYG builder. I used Material parameter collections so I could bulk edit materials more easily. This is
especially true for the grass.

Please check the descriptions of my blueprint functions, classes and properties. This is why I have explained how my
code works.
***
<h2> UMG Class Tree structure </h2>
<ul>
<li> UDiorama_UserWidget </li>
    <ul> 
        <li> UDiorama_PropertiesPanelWidget </li>
        <li> UDiorama_PropertiesGroupWidget </li>
        <li> UDiorama_PropertyWidget </li>
        <ul>
            <li> UDiorama_NumericPropertyWidget </li>
            <li> UDiorama_ColourPropertyWidget </li>
        </ul>
    </ul>
</ul>
<ul>
<li> IWindowUMGInterface </li>
    <ul>
        <li> UDiorama_PropertiesPanelWidget </li>
    </ul>
</ul>

***



<h2> References </h2>
<ul>
<h3>Shader Tutorials</h3>
<ul>
<li><a href="https://youtu.be/FT-QfuzoQEk?si=4oRPoCRn11KOthEw">Grass Tutorial</a>.</li>
 <li><a href="https://youtube.com/playlist?list=PL5Rt3cak7KNGhjhIWZtx9wCjBn7HXex-l&si=alVTodhPvQohAdho"> Day Night Cycle Tutorial and textures</a>. </li>
 </ul>
 <h3> Particle Tutorials </h3>
 <ul>
 <li><a href="https://www.youtube.com/watch?v=L90sQA8MxS4">Smoke particle tutorial and texture</a>. </li>
 <li> <a href="https://www.youtube.com/watch?v=s_UQYuM1RWU">Rain particle tutorial</a>. </li>
 <li>The water shader was created from Daryl's water shader tutorial for Unreal.</li>
 </ul>
 <h3> Models </h3>
    <ul>
 <li>Grass blade model by Joe.</li>
<li> Rest of the models and materials are from <a href=https://Quixel.com>Quixel</a>.</li>
 </ul>

 <h2> Sound Effects </h2>
    <ul>
<li> Bird sound effect from the Unreal Stater Content. </li>
<li> Owl sound effect from <a href="https://pixabay.com">Pixabay</a>.</li>
<li> Rain sound effect from <a href="https://SoundJay.com"> Sound Jay</a>. </li>
</ul>
</ul>

