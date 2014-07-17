#include "WormActions.h"
#define FUERZA_MOV 90
#define JUMP_IMPULSE 70
#define CLIMB_FACTOR 1.2
#define JUMP_TIMEOUT 15
#define JUMP_WIDTH_FACTOR 3.5

WormActions::WormActions(Worm2d* worm2d)
{
	this->deltaMovement=1/(float)ESCALA_UL2PX; //desplazamiento
	this->jumpTimeOut = 0;
	this->aWorm2d=worm2d;

}

void WormActions::jump()
{	
	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() && (this->jumpTimeOut < 0) )
	{
		this->aWorm2d->body->SetLinearVelocity(b2Vec2(0,0) );
		float impulse = this->aWorm2d->body->GetMass() * 10;
        this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(0,impulse), this->aWorm2d->body->GetWorldCenter() );
		//this->aWorm2d->body->SetLinearVelocity( b2Vec2(1,1) );
		this->jumpTimeOut = JUMP_TIMEOUT;
    }
}


void WormActions::jumpRight()
{	
	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() && (this->jumpTimeOut < 0) )
	{
		this->aWorm2d->body->SetLinearVelocity(b2Vec2(0,0) );
        float impulse = this->aWorm2d->body->GetMass() * 10;
        this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(impulse/JUMP_WIDTH_FACTOR,impulse), this->aWorm2d->body->GetWorldCenter() );

		this->jumpTimeOut = JUMP_TIMEOUT;
    }
}


void WormActions::jumpLeft()
{	
			
	if ( static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() && (this->jumpTimeOut < 0) )
	{
		this->aWorm2d->body->SetLinearVelocity(b2Vec2(0,0) );
        float impulse = this->aWorm2d->body->GetMass() * 10;
		this->aWorm2d->body->ApplyLinearImpulse( b2Vec2(-impulse/JUMP_WIDTH_FACTOR,impulse), this->aWorm2d->body->GetWorldCenter() );
		this->jumpTimeOut = JUMP_TIMEOUT;
    }
}

void WormActions::moveLeft()
{
	
	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();
	////printf("\ntrying to move left %f, %f, jumping: %d, grounded: %d",nx, ny, static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping(),
		//static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() );

	if ( !static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping() && static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() ){
		
		if ( nx > 0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*CLIMB_FACTOR*ny,FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV*CLIMB_FACTOR*ny,FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}
		if (nx <= 0.02 || nx >= -0.02){
			
			this->aWorm2d->body->ApplyForce( b2Vec2(-FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

	}
}

void WormActions::moveRight()
{

	float nx = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalX();
	float ny = static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->getNormalY();
	////printf("\ntrying to move right %f, %f, jumping: %d, grounded: %d",nx, ny, static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping(),
		//static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() );

	if ( !static_cast<Worm*>(this->aWorm2d->body->GetUserData())->isJumping() && static_cast<GameElement*>(this->aWorm2d->body->GetUserData())->isGrounded() ){

		if (nx > 0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*CLIMB_FACTOR*ny,-FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx < -0.02 && ny > 0.15){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV*CLIMB_FACTOR*ny,-FUERZA_MOV*CLIMB_FACTOR*nx), this->aWorm2d->body->GetWorldCenter() );
			return;
		}

		if (nx <= 0.02 || nx >= -0.02){
			this->aWorm2d->body->ApplyForce( b2Vec2(FUERZA_MOV,0), this->aWorm2d->body->GetWorldCenter() );
			return;
		}
	}

}

WormActions::~WormActions()
{

}
